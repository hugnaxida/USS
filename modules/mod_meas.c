/***************************************************************************//**
 * @file      mod_meas.c
 *
 * @creator   StSl
 * @created   17.10.2017
 * @sdfv      Demo Flow
 *
 * @brief     Measurement Control software module
 *
 * @purpose
 *
 * Software module for managing and controlling echo related measurement processes.
 *
 * @image html "sequencechartecho measurement.png" "Sequence-chart: start measurement" max-width=640
 * <a href="sequencechartecho measurement.png">klick here to enlarge image</a>
 *
 * ******************************************************************************
 *
 * Demo Code Usage Restrictions:
 * Elmos Semiconductor AG provides this source code file simply and solely for
 * IC evaluation purposes in laboratory and this file must not be used
 * for other purposes or within non laboratory environments. Especially, the use
 * or the integration in production systems, appliances or other installations is
 * prohibited.
 *
 * Disclaimer:
 * Elmos Semiconductor AG shall not be liable for any damages arising out of
 * defects resulting from
 * (1) delivered hardware or software,
 * (2) non observance of instructions contained in this document, or
 * (3) misuse, abuse, use under abnormal conditions or alteration by anyone
 * other than Elmos Semiconductor AG. To the extend permitted by law
 * Elmos Semiconductor AG hereby expressively disclaims and user expressively
 * waives any and all warranties of merchantability and of fitness for a
 * particular purpose, statutory warranty of non-infringement and any other
 * warranty or product liability that may arise by reason of usage of trade,
 * custom or course of dealing.
 *
 ******************************************************************************
 *
 * $Id: mod_meas.c 406 2019-02-08 15:49:42Z siko $
 *
 * $Revision: 406 $
 *
 ******************************************************************************/

/* ****************************************************************************/
/* ******************************** INCLUDES **********************************/
/* ****************************************************************************/
#include "mod_meas.h"
#include "mod_dsi3_cfg.h"
#include "mod_app.h"
#include "mod_lab.h"
#include "mod_util.h"
#include "mod_err.h"
#include "mod_dsp.h"
#include "string.h"
#include "stdbool.h"

/* ****************************************************************************/
/* **************************** CUSTOM INCLUDES *******************************/
/* ****************************************************************************/


/* ****************************************************************************/
/* *************************** DEFINES AND MACROS *****************************/
/* ****************************************************************************/
#define swtimer_IRQ_EVT_CNT_ZERO_SyncTimer            swtimer_IRQ_EVT_CNT_ZERO_1
#define swtimer_IRQ_EVT_CNT_ZERO_TickPeriodTimer      swtimer_IRQ_EVT_CNT_ZERO_0

#define NOISE_MEASUREMENT_SAMPLING_PERIOD         (32u)       /**< us period for noise measurement */
#define OFFSET_DSI3SYNCPULSE_TO_DSI3TIMER         (12u)       /**< us offset between dsi sync pulse and its recognition by the dsi3 timer */
#define TIME_CRMSYNC_TO_NOISE_MEASUREMENT         (768u)      /**< us time buffer between CRM command and noise measurements    - empirically determined value */
#define TIME_NOISE_MEASUREMENT_TO_ECHO_DETECTION  (512u)      /**< us time buffer between noise measurement and echo detection  - empirically determined value */
#define MEASUREMENT_TIMER_MAX                     (0xFFFFu)   /**< maximum value of the measurement timer */
#define ECHO_MEASUREMENT_NOISE_MONITORING_PERIOD  (32u-1u)    /**< Period in 32us in which the noise is monitored while an echo measurement cycle is running */
#define BRG_STATUS_BURST_RUNNING                  (1u)        /**< BRG status indicates a running burst */
#define TDR_STATUS_NORMAL_OPERATION               (0u)        /**< TDR status indicates normal operation in burst phase */
#define SYSTEM_TIMER_PERIOD                       (32u)       /**< Timer period, on which most time constants in the config are based */
#define STG_POSITIVE_CURVE_GRADIENT               (1u)        /**< Sets the stg curve to have a positive gradient */
#define STG_NEGATIVE_CURVE_GRADIENT               ((uint8_t)(-1))/**< Sets the stg curve to have a negative gradient */
#define FREQUENCY_CORRECTION_VALUE                (768u)      /**< correction value for frequency calibration (see datasheet) */
#define ENVP_CFG_BW_4                             (0x4u)      /**< Value of ENVP_CFG for f(-3db) = 0.0838 * fc */
#define ENVP_CFG_BW_5                             (0x5u)      /**< Value of ENVP_CFG for f(-3db) = 0.0412 * fc */
#define ENVP_CFG_BW_6                             (0x6u)      /**< Value of ENVP_CFG for f(-3db) = 0.0204 * fc */

#define BURST_CNT_0                               (0u)        /**< Number of bursts = 0 */
#define BURST_CNT_8                               (8u)        /**< Number of bursts = 8 */
#define BURST_CNT_28                              (28u)       /**< Number of bursts = 28 */

#define BITMASK_OVER_VOLTAGE_AT_VTANK_DURING_BURST (8u)
#define MIN_TIME_MEAS_TASK_TO_STATEPREECHOMEAS    (2800)
#define NO_MONITOR_DATA_SELECTED                  (0u)        /**< no Monitor Channels are active */
#define DSP_MT_OFF                                (0x07FFu)   /**< DSP Measurement Timer is not active */ 

/* ****************************************************************************/
/* *********************** STRUCTS, ENUMS AND TYPEDEFS ************************/
/* ****************************************************************************/
typedef struct
{
  uint16_t      Interval1;        /**< STG - Time to first change of STG parameters in HW */
  uint16_t      Interval2;        /**< STG - Time to second change of STG parameters in HW */
  uint16_t      Interval3;        /**< STG - Time to third change of STG parameters in HW */
  uint16_t      Interval4;        /**< STG - Time to forth change of STG parameters in HW */
  uint16_t      TimeBase1;        /**< STG - Timebase for STG curve after first Interval */
  uint16_t      TimeBase2;        /**< STG - Timebase for STG curve after second Interval */
  uint16_t      TimeBase3;        /**< STG - Timebase for STG curve after third Interval */
  uint16_t      Gradient1;        /**< STG - Gradient for STG curve after first Interval */
  uint16_t      Gradient2;        /**< STG - Gradient for STG curve after second Interval */
  uint16_t      Gradient3;        /**< STG - Gradient for STG curve after third Interval */
} sPreCalcParam_StgParam_t;

typedef struct
{
  uint16_t      StcStart;
  uint16_t      StcMod;
  uint16_t      StcGain;
  uint16_t      StcTb;
} sPreCalcParam_StcParam_t;

/* ****************************************************************************/
/* ***************************** GLOBAL VARIABLES *****************************/
/* ****************************************************************************/
sPreCalcParam_StgParam_t preCalculatedStgParam; /* struct of precalculated parameters for stg variation */
sPreCalcParam_StcParam_t preCalculatedStcParam; /* struct of precalculated parameters for stc variation */

/* ****************************************************************************/
/* ************************ MODULE GLOBALE VARIABLES **************************/
/* ****************************************************************************/
Dsi3Drv_sMeasCtrl_t loc_AppRtData;  /* application runtime data environment */
/* ****************************************************************************/
/* ************************** FUNCTION PROTOTYPES *****************************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * Check TDR status after burst
 *
 * Checks, if the TDR had an error during burst and sets the related error flag
 * heck if drv1/drv2/drvs failure flag is set after burst
 *
 * SM22: Driver voltage monitoring
 * (for details see SafetyManual)
 *
 * @return      -
 * ****************************************************************************/
void loc_check_TdrStat(void);

/* **************************************************************************//**
 * @brief
 * Start Synchronization Timer
 *
 * Configures and starts the synchronization timer to measure the time between:
 * Begin of the Noise Measurement and begin of the echo measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_StartSyncTimerForEchoMeas(void);

/* **************************************************************************//**
 * @brief
 * Start Synchronization Timer
 *
 * Configures and starts the synchronization timer to measure the time between:
 * Begin of the Echo Measurement and end of the masking time
 *
 * @return      none
 * ****************************************************************************/
void loc_StartSyncTimerForPostMaskingTime(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Init
 *
 * Initializes all registers for the upcoming measurement and the diagnostic measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT(void);

/* **************************************************************************//**
 * @brief
 * Start Tick Timer for Echo Measurement
 *
 * Configures and starts the tick timer to trigger every 32us
 * for monitoring the echo measurement process
 *
 * @return      none
 * ****************************************************************************/
void loc_StartTickTimerForEchoMeas(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Init subfunction Common
 *
 * Initializes all registers for the upcoming measurement and the diagnostic measurement
 * that are common for standard and advanced measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_Com(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Init subfunction Standard
 *
 * Initializes all registers for the upcoming measurement and the diagnostic measurement
 * that are specific for standard measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_Std(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Init subfunction Advanced
 *
 * Initializes all registers for the upcoming measurement and the diagnostic measurement
 * that are specific for advanced measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_Adv(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Init subfunction Noise
 *
 * Initializes all registers for the upcoming measurement and the diagnostic measurement
 * that are specific for noise measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_Noise(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Noise Measurement
 *
 * Acquires and stores a noise sample from envelope data
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_NOISE_MEAS(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Initialize Echo Measurement
 *
 * Initializes all registers for the upcoming measurement
 * that have been modified for the noise measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_ECHO_MEAS(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Initialize Echo Measurement subfunction Standard
 *
 * Initializes all registers for the upcoming measurement
 * that have been modified for the noise measurement
 * which are specific for standard measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_ECHO_MEAS_Std(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Initialize Echo Measurement subfunction Standard
 *
 * Precalculates all standard measurement related parameters
 *
 * @param       loc_pParam      Pointer to std meas parameter struct
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_PreCalcParam_INIT_ECHO_MEAS_Std(Meas_uStandardPathProfile* loc_pParam);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Initialize Echo Measurement subfunction Advanced
 *
 * Initializes all registers for the upcoming measurement
 * that have been modified for the noise measurement
 * which are specific for advanced measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_ECHO_MEAS_Adv(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Initialize Echo Measurement subfunction Near field detection
 *
 * Initializes all registers for the upcoming near field detection
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_ECHO_MEAS_Nfd(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Echo Measurement asynchronous
 *
 * Runs echo measurement related controlling tasks in the main loop
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_ECHO_MEAS_async(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Echo Measurement Manage STC and STG
 *
 * sets sensitivity time control registers at its start point and
 * changes static threshold generation registers over time
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_ECHO_MEAS_manage_stc_and_stg(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Echo Measurement synchronous
 *
 * Runs echo measurement related controlling tasks, triggered by the tick timer
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_ECHO_MEAS_sync(void);

/* **************************************************************************//**
 * @brief
 * Function related to Task State Post Measurement
 *
 * Cleans up after measurement has been finished or aborted
 * and switches back to idle state
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_POST_MEAS(void);

/* **************************************************************************//**
 * @brief
 * Read back after write
 *
 * Compares written register values to the value we expect in that register
 *
 * @param       dataFromRegister    data from register which should be compared
 * @param       dataExpected        data which should have been saved into the register
 *
 * @return      none
 * ****************************************************************************/
void loc_readBackAfterWrite(uint16_t dataFromRegister, uint16_t dataExpected);

/* **************************************************************************//**
 * @brief
 * Check for Abortion
 *
 * Checks, if the measurement abortion flag has been set and
 * executes the abortion
 *
 * @return      true  if measurement has been aborted
 *              false if measurement will continue
 * ****************************************************************************/
bool_t loc_checkForAbortion(void);

/* ****************************************************************************/
/* ************************** FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * Initialization
 *
 * Initialization function for the measurement module
 *
 * @return      TRUE  always
 * ****************************************************************************/
bool_t meas_init(void)
{
  bool_t retval = true;

  /* initialize measurement state machine */
  loc_AppRtData.CurrentState = meas_eMeas_STATE_IDLE;

  /* Register the timer callbacks */
  retval = retval && swtimer_RegisterCustomZeroCountInterruptCallback(swtimer_eTickPeriodTimer, meas_TickTimer_ISR);
  retval = retval && swtimer_RegisterCustomZeroCountInterruptCallback(swtimer_eSyncTimer, meas_SyncTimer_ISR);

  return retval;
}

/* **************************************************************************//**
 * @brief
 * Get Control
 *
 * Makes measurement related application data accessible by a pointer
 *
 * @return      pointer to measurement related application data
 * ****************************************************************************/
Dsi3Drv_pMeasCtrl_t meas_GetCtrl(void)
{
  return &loc_AppRtData;
}

/* **************************************************************************//**
 * @brief
 * Main Task
 *
 * Handles the measurement state machine of the measurement module
 *
 * @image html "meas_Task.png" "Activity Diagram: Measurement task" max-width=640
 * <a href="meas_Task.png">klick here to enlarge image</a>
 *
 * @image html "statemachineecho measurement.png" "State machine: measurement" max-width=640
 * <a href="statemachineecho measurement.png">klick here to enlarge image</a>
 *
 * @return      none
 * ****************************************************************************/
/*
meas_Task() 函数是一个处理测量模块状态机的主要任务函数。它通过 switch-case 语句根据当前状态 (loc_AppRtData.CurrentState) 来执行不同的任务流程。以下是各状态及其对应的功能描述：
1. meas_eMeas_STATE_IDLE： 当前处于空闲状态，无任何操作。2. meas_eMeas_STATE_INIT： 初始化即将开始的测量所需寄存器，并将状态切换至诊断测量状态（meas_eMeas_STATE_DIAG_MEAS）。
3. meas_eMeas_STATE_DIAG_MEAS： 执行诊断测量，例如测量 Vcc（电源电压）和温度，并将结果存储在 loc_AppRtData.Results 中。然后进入预噪声测量等待状态（meas_eMeas_STATE_PRE_NOISE_MEAS）。
4. meas_eMeas_STATE_PRE_NOISE_MEAS： 开始噪声测量定时器，准备进行噪声数据采集，并切换到噪声测量状态（meas_eMeas_STATE_NOISE_MEAS）。
5. meas_eMeas_STATE_NOISE_MEAS： 在回波检测开始之前，通过周期性定时器中断（swtimer_eTickPeriodTimer）进行噪声测量。
6. meas_eMeas_STATE_INIT_ECHO_MEAS： 初始化即将进行的回波测量所需的寄存器，并切换到预回波测量等待状态（meas_eMeas_STATE_PRE_ECHO_MEAS）。
7. meas_eMeas_STATE_PRE_ECHO_MEAS： 等待回波测量阶段开始，由另一个定时器中断（swtimer_eSyncTimer）触发。
8. meas_eMeas_STATE_ECHO_MEAS_MASKED 和 meas_eMeas_STATE_ECHO_MEAS： 控制回波测量的过程，其中 meas_eMeas_STATE_ECHO_MEAS_MASKED 可能是在某个条件下进行的特殊处理，
meas_eMeas_STATE_ECHO_MEAS 通过异步方式调用 loc_TaskState_ECHO_MEAS_async() 函数来执行回波测量任务。9. meas_eMeas_STATE_POST_LAB 和 
meas_eMeas_STATE_POST_MEAS： 这两个状态都涉及到测量后的处理阶段，前者可能特指实验室模式下的操作，后者为通用后处理阶段，都会调用 loc_TaskState_POST_MEAS() 函数进行数据后期处理。
最后，函数会检查是否存在终止标记，如果设置了abort（终止）标志，则会执行相应的操作。整体来看，这个函数按照测量的不同阶段有序地管理测量状态机，依次完成诊断、噪声测量、回波测量以及后期处理等任务。
*/
void meas_Task(void)
{
  switch(loc_AppRtData.CurrentState)
  {
  case meas_eMeas_STATE_IDLE:
    /* noting to do here */
    break;
  case meas_eMeas_STATE_INIT:
    /* initiate registers for upcoming measurement */
    loc_TaskState_INIT();
    /* switch to diagnose state */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_DIAG_MEAS;
    break;
  case meas_eMeas_STATE_DIAG_MEAS:
    /* diagnostic measurement of Vcc and Temperature */
    app_DiagnosticMeasurement(&(loc_AppRtData.Results));
    /* switch to the pre noise meas wait state */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_PRE_NOISE_MEAS;
    break;
  case meas_eMeas_STATE_PRE_NOISE_MEAS:
    /* Start the noise measurement timer, which will acquire the noise data */
    meas_StartTickTimerForNoiseMeas();
    /* Begin the noise measurement phase */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_NOISE_MEAS;
    break;
  case meas_eMeas_STATE_NOISE_MEAS:
    /*
     * measure noise before the echo detection begins
     * done by periodic timer interrupt of swtimer_eTickPeriodTimer
     */
    break;
  case meas_eMeas_STATE_INIT_ECHO_MEAS:
    /* initiate registers for upcoming measurement */
    loc_TaskState_INIT_ECHO_MEAS();
    /* switch to the pre echo meas wait state */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_PRE_ECHO_MEAS;
    break;
  case meas_eMeas_STATE_PRE_ECHO_MEAS:
     /*
     * wait for the echo measurement phase to begin
     * done by timer interrupt of swtimer_eSyncTimer
     */
    break;
  case meas_eMeas_STATE_ECHO_MEAS_MASKED:
      /*
     * wait for the echo measurement phase to begin
     * done by timer interrupt of swtimer_eSyncTimer
     */
  case meas_eMeas_STATE_ECHO_MEAS:
    /* control echo measurement */
    loc_TaskState_ECHO_MEAS_async();
    break;
  
  case meas_eMeas_STATE_POST_LAB:
    /* state for lab-mode to deactivate timers */
    /* fall through */
        
  case meas_eMeas_STATE_POST_MEAS:
    /* post processing phase */ 
    loc_TaskState_POST_MEAS();
    break;

  default:
    /* this case is impossible */
    break;
  }

  /* check if abortion flag has been set */
  (void)loc_checkForAbortion();
}

/* **************************************************************************//**
 * @brief
 * Start a Standard Measurement
 *
 * Initiates a standard measurement cycle by setting all given
 * parameters & starting the synchronization timer
 *
 * @param       conf         Selected direct or indirect measurement
 * @param       mode         Selected measurement mode
 * @param       profile      Selected measurement profile
 * ****************************************************************************/
void meas_StartStandardMeasurement(Meas_eMeasurementConf_t conf, Meas_eMeasurementMode_t mode, Meas_eMeasurementProfile_t profile)
{
  /* set the kind of measurement to standard */
  loc_AppRtData.RuntimeData.MeasurementKind = meas_eMeasKind_STANDARD;
  /* set the measurement mode & configuration & profile */
  loc_AppRtData.RuntimeData.MeasurementMode = mode;
  loc_AppRtData.RuntimeData.MeasurementConf = conf;
  loc_AppRtData.RuntimeData.MeasurementProfile = profile;
  
  /* only trigger state-machine if Configuration is not "no measurement" */
  if(conf != meas_eMeasConf_NONE)
  {
    /* switch measurement state machine to init state to start the measurement */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_INIT;
    /* start timer for synchronization */
    loc_StartSyncTimerForEchoMeas();
    /* reset measurement flags */
    app_ResetMeasurementFlagsCritical(&(loc_AppRtData.Results));
  }
  else
  {
    /* dont execute if NONE measurement has been chosen */
  }
}

/* **************************************************************************//**
 * @brief
 * Start an Advanced Measurement
 *
 * Initiates an advanced measurement cycle by setting all given
 * parameters & starting the synchronization timer
 *
 * @param       conf         Selected direct or indirect measurement
 * @param       mode         Selected measurement mode
 * @param       profile      Selected measurement profile
 * @return      none
 * ****************************************************************************/
void meas_StartAdvancedMeasurement(Meas_eMeasurementConf_t conf, Meas_eMeasurementMode_t mode, Meas_eMeasurementProfile_t profile)
{
  /* set the kind of measurement to advanced */
  loc_AppRtData.RuntimeData.MeasurementKind = meas_eMeasKind_ADVANCED;
  /* set the measurement mode & configuration & profile */
  loc_AppRtData.RuntimeData.MeasurementMode = mode;
  loc_AppRtData.RuntimeData.MeasurementConf = conf;
  loc_AppRtData.RuntimeData.MeasurementProfile = profile;
  
  /* only trigger state-machine if Configuration is not "no measurement" */
  if(conf != meas_eMeasConf_NONE)
  {
    /* switch measurement state machine to init state to start the measurement */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_INIT;
    /* start timer for synchronization */
    loc_StartSyncTimerForEchoMeas();
    /* reset measurement flags */
    app_ResetMeasurementFlagsCritical(&(loc_AppRtData.Results));
  }
  else
  {
    /* dont execute if NONE measurement has been chosen */
  }
}

/* **************************************************************************//**
 * @brief
 * Abort Measurement
 *
 * Sets the measurement abort flag, to stop the active measurement cycle
 *
 * @return      none
 * ****************************************************************************/
void meas_AbortMeasurement(void)
{
  /* set measurement abort flag */
  loc_AppRtData.RuntimeData.MeasAbortFlag = TRUE;
}

/* **************************************************************************//**
 * @brief
 * Get Measurement Configuration
 *
 * Returns the measurement configuration of the active measurement, which indicates if a
 * direct, indirect or none measurement is executed
 *
 * @return      Measurement Configuration of active measurement
 * ****************************************************************************/
Meas_eMeasurementConf_t meas_GetMeasConf(void)
{
  return loc_AppRtData.RuntimeData.MeasurementConf;
}

/* ****************************************************************************/
/* ******************** LOCAL FUNCTION DEFINITIONS ****************************/
/* ****************************************************************************/

/* **************************************************************************//**
 * @brief
 * Synchronization Timer Interrupt Service Routine
 *
 * Triggers measurement state changes synchronously to the CRM sync pulse
 *
 * @param       sno             Triggered interrupt event number
 * @param       contextdata     Pointer to SCI context data
 * @return      none
 * ****************************************************************************/
void meas_SyncTimer_ISR(swtimer_eInterruptVectorNum_t sno,  swtimer_pInterruptContextData_t contextdata)
{
  SWT_IRQ_DISABLE(swtimer_IRQ_EVT_CNT_ZERO_SyncTimer);
  SWT_CTRL_IRQ_CLEAR(swtimer_IRQ_EVT_CNT_ZERO_SyncTimer);
  SWT_DISABLE(swtimer_eSyncTimer);

  switch(loc_AppRtData.CurrentState)
  {
  case meas_eMeas_STATE_PRE_ECHO_MEAS:
    /* reset measurement timer */
    loc_AppRtData.Results.MeasurementTime = 0u;
    
    /* Check if lab mode is active */
    if(true == loc_AppRtData.Results.LabModeRuntimeData.IsInitialised)
    {
      /* start lab mode if start delay is reached */
      if((false == loc_AppRtData.Results.LabModeRuntimeData.IsRunning) && (false == loc_AppRtData.Results.LabModeRuntimeData.IsFinished)
          && (loc_AppRtData.Results.MeasurementTime >= loc_AppRtData.Results.LabModeRuntimeData.MonStart))
      {
        lab_StartLabMode();
      }
    }

    /* begin the echo measurement phase */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_ECHO_MEAS_MASKED;
    
    /* Start the tick timer for monitoring of the measurement process */
    loc_StartTickTimerForEchoMeas();

    /* Trigger the start of the measurement */
    BRG_CTRL_START();

    /* compensate first 32us isr timer tick in burst-length monitoring see SM10 */
    if(BRG_ON == BRG_STATUS_GET() )
    {
      loc_AppRtData.Results.BurstMonitoring.BurstLength++;
    }
    else
    {
      /* do nothing */
    }
      
    /* Immediately start the sync timer for the masking timeout */
    loc_StartSyncTimerForPostMaskingTime();

    break;
  case meas_eMeas_STATE_ECHO_MEAS_MASKED:
    /* enable dma interrupts */
    app_ActivateDmaForEchoMeas(loc_AppRtData.RuntimeData.MeasurementKind);
    /* switch to active measurement state */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_ECHO_MEAS;
    break;
  default:
    /* all other cases should be impossible */
    break;
  }
}

/* **************************************************************************//**
 * @brief
 * Noise Measurement Timer Interrupt Service Routine
 *
 * Is triggered with a period of 32us to acquire a new noise sample
 *
 * @param       sno               Triggered interrupt event number
 * @param       contextdata       Pointer to SCI context data
 * @return      none
 * ****************************************************************************/
void meas_TickTimer_ISR(swtimer_eInterruptVectorNum_t sno,  swtimer_pInterruptContextData_t contextdata)
{
  /* increment measurement timer (gets reset on measurement start) */
  ++(loc_AppRtData.Results.MeasurementTime);

  if ( DSP_MT_OFF != DSP_MT_TIME() )
  {
    /* because MeasurementTime is always cut of while dividing with 32us, so it runs before DSP_MT_TIME 
       that is why one 32us tick ia added */
    loc_AppRtData.Results.SyncedMeasurementTime = (DSP_MT_TIME()>>5u)+1u;
  }
  else
  {
    /* the measurement timer is not active so no measurement is done */
    loc_AppRtData.Results.SyncedMeasurementTime = 0u;
  }

  /* Check if lab mode is active */
  if(true == loc_AppRtData.Results.LabModeRuntimeData.IsInitialised)
  {
    /* start lab mode if start delay is reached */
    if((false == loc_AppRtData.Results.LabModeRuntimeData.IsRunning) && (false == loc_AppRtData.Results.LabModeRuntimeData.IsFinished)
        && (loc_AppRtData.Results.SyncedMeasurementTime >= loc_AppRtData.Results.LabModeRuntimeData.MonStart))
    {
      if((meas_eMeas_STATE_ECHO_MEAS_MASKED == loc_AppRtData.CurrentState) ||
          (meas_eMeas_STATE_ECHO_MEAS == loc_AppRtData.CurrentState) ||
          (meas_eMeas_STATE_POST_MEAS == loc_AppRtData.CurrentState))
      {
        lab_StartLabMode();
      }
    }
    else
    {
      /* timer is not needed anymore */
      if(meas_eMeas_STATE_POST_MEAS == loc_AppRtData.CurrentState)
      {
        /* deactivate the timer */
        loc_AppRtData.CurrentState = meas_eMeas_STATE_POST_LAB;
      }
    }
  }
  else
  {
    /* timer are stoped in idle state, set in post measurement task */
  }

  /* state machine */
  switch(loc_AppRtData.CurrentState)
  {
  case meas_eMeas_STATE_NOISE_MEAS:
    /* do noise measurement */
    loc_TaskState_NOISE_MEAS();
    break;

  case meas_eMeas_STATE_ECHO_MEAS_MASKED:
    /*fall through*/
  case meas_eMeas_STATE_ECHO_MEAS:
    loc_TaskState_ECHO_MEAS_manage_stc_and_stg();
    loc_TaskState_ECHO_MEAS_sync();
    if (false == loc_AppRtData.Results.LabModeRuntimeData.IsInitialised)
    {
      app_NearFieldDetection(&loc_AppRtData, loc_AppRtData.Results.MeasurementTime);
    }
    break;

  case meas_eMeas_STATE_POST_LAB:
      /* stop timer */
      SWT_IRQ_DISABLE(swtimer_IRQ_EVT_CNT_ZERO_TickPeriodTimer);
      SWT_CTRL_IRQ_CLEAR(swtimer_IRQ_EVT_CNT_ZERO_TickPeriodTimer);
      SWT_DISABLE(swtimer_eTickPeriodTimer);
    break;

  default:
    /*
     * this callback shouldn't be called in another state
     * BUT it could if the controller is very busy while measuring
     * so this case changes the state to meas_eMeas_STATE_POST_MEAS to
     * stop the measurement and prevent false measurement results
     */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_POST_MEAS;
    break;
  }
}

/* **************************************************************************//**
 * @brief
 * Start Synchronization Timer
 *
 * Configures and starts the synchronization timer to measure the time between:
 * Begin of the Noise Measurement and begin of the echo measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_StartSyncTimerForEchoMeas(void)
{
  /*
   * set counter to generate a pulse, exactly
   * (TIME_NOISE_MEASUREMENT_TO_ECHO_DETECTION + loc_AppRtData.Parameters.data.NoiseMeasurement.fields.NoiseMeasTime)
   * after the start of the noise measurement.
   */
  SWT_CNT_RELOAD_SET(swtimer_eSyncTimer, 0xFFFF);
  SWT_RESTART_TIMER(swtimer_eSyncTimer);
  SWT_ENABLE(swtimer_eSyncTimer);

  uint16_t timerReloadValForEchoStart = TIME_NOISE_MEASUREMENT_TO_ECHO_DETECTION + (loc_AppRtData.Parameters.data.NoiseMeasurement.fields.NoiseMeasTime * SYSTEM_TIMER_PERIOD) \
                                        + TIME_CRMSYNC_TO_NOISE_MEASUREMENT - OFFSET_DSI3SYNCPULSE_TO_DSI3TIMER;
  if ( MIN_TIME_MEAS_TASK_TO_STATEPREECHOMEAS < (int32_t)( timerReloadValForEchoStart - DSI3_CTRL_TIMER_COUNTER() ) ) /* todo: 2600us typical time to get to Task until meas_eMeas_STATE_PRE_ECHO_MEAS is reached */
  {
    SWT_CNT_RELOAD_SET(swtimer_eSyncTimer, timerReloadValForEchoStart - DSI3_CTRL_TIMER_COUNTER());
    SWT_RESTART_TIMER(swtimer_eSyncTimer);

    SWT_IRQ_ENABLE(swtimer_IRQ_EVT_CNT_ZERO_SyncTimer);
  }
  else
  {
    /* not synchronous anymore, call SyncTimer ISR and continue processing the statemachine 
       this is in case of self-test e.g. */
    SWT_CNT_RELOAD_SET(swtimer_eSyncTimer, timerReloadValForEchoStart);
    SWT_RESTART_TIMER(swtimer_eSyncTimer);
    SWT_IRQ_ENABLE(swtimer_IRQ_EVT_CNT_ZERO_SyncTimer);
  }

}

/* **************************************************************************//**
 * @brief
 * Start Synchronization Timer
 *
 * Configures and starts the synchronization timer to measure the time between:
 * Begin of the Echo Measurement and end of the masking time
 *
 * @return      none
 * ****************************************************************************/
void loc_StartSyncTimerForPostMaskingTime(void)
{
  /* check if masking time is activated */
  if(0 != loc_AppRtData.RuntimeData.MaskingTime)
  {
    /* MaskingTime -> time in which measurement results are invalid (times 32us) */
    SWT_CNT_RELOAD_SET(swtimer_eSyncTimer, loc_AppRtData.RuntimeData.MaskingTime * SYSTEM_TIMER_PERIOD);
    SWT_IRQ_ENABLE(swtimer_IRQ_EVT_CNT_ZERO_SyncTimer);
    SWT_ENABLE(swtimer_eSyncTimer);
    SWT_RESTART_TIMER(swtimer_eSyncTimer);
  }
  else
  {
    /* call SyncTimer ISR to skip masking time and continue processing the statemachine - parameters are not used in ISR */
    meas_SyncTimer_ISR(swtimer_IRQ_EVT_CNT_ZERO_0, (swtimer_pInterruptContextData_t) NULL);
  }
}

/* **************************************************************************//**
 * @brief
 * Start Tick Timer for Noise Measurement
 *
 * Configures and starts the tick timer to trigger
 * noise sampling every 32us
 *
 * @return      none
 * ****************************************************************************/
void meas_StartTickTimerForNoiseMeas(void)
{
  /*
   * set counter to fire an interrupt every 32us to save a sample
   * for the noise measurement
   */
  SWT_CNT_RELOAD_SET(swtimer_eTickPeriodTimer, NOISE_MEASUREMENT_SAMPLING_PERIOD-1);
  SWT_IRQ_ENABLE(swtimer_IRQ_EVT_CNT_ZERO_TickPeriodTimer);
  SWT_ENABLE(swtimer_eTickPeriodTimer);
  SWT_AUTOCYCLE_ENABLE(swtimer_eTickPeriodTimer);
  SWT_RESTART_TIMER(swtimer_eTickPeriodTimer);
}

/* **************************************************************************//**
 * @brief
 * Start Tick Timer for Echo Measurement
 *
 * Configures and starts the tick timer to trigger every 32us
 * for monitoring the echo measurement process
 *
 * @return      none
 * ****************************************************************************/
void loc_StartTickTimerForEchoMeas(void)
{
  /*
   * set counter to fire an interrupt every 32us to save a sample
   * for the noise measurement
   */
  SWT_CNT_RELOAD_SET(swtimer_eTickPeriodTimer, ECHO_MEASUREMENT_MONITORING_PERIOD-1);
  SWT_IRQ_ENABLE(swtimer_IRQ_EVT_CNT_ZERO_TickPeriodTimer);
  SWT_ENABLE(swtimer_eTickPeriodTimer);
  SWT_AUTOCYCLE_ENABLE(swtimer_eTickPeriodTimer);
  SWT_RESTART_TIMER(swtimer_eTickPeriodTimer);
}

/* **************************************************************************//**
 * @implementation
 * Function related to Task State Init
 *
 * Initializes all registers for the upcoming measurement and the diagnostic measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT(void)
{
  /* Cleanup old measurement data & config */
  /* reset abort flag */
  loc_AppRtData.RuntimeData.MeasAbortFlag = FALSE;
  /* disable dma and reset result buffer */
  app_MeasurementInit(&(loc_AppRtData.Results));

  loc_AppRtData.Results.NoiseAtgThreshold = loc_AppRtData.Parameters.data.NoiseMeasurement.fields.NoiseAtgThreshold;

  if(meas_eMeasKind_STANDARD == loc_AppRtData.RuntimeData.MeasurementKind)
  {
    /* standard measurement */
    /* profile set -> write registers */
    loc_TaskState_INIT_Com();
    loc_TaskState_INIT_Std();
    loc_TaskState_INIT_Noise();
  }
  else/*-?|AP5|wladimir.pauls|c1|*/
  {/*-|AP5|wladimir.pauls|c1|?*/
    /* advanced measurement */
    if( (meas_eMeasProfile_PROFILEA == loc_AppRtData.RuntimeData.MeasurementProfile) ||
        (meas_eMeasProfile_PROFILEB == loc_AppRtData.RuntimeData.MeasurementProfile)    )
    {
      /* profile set -> write registers */
      loc_TaskState_INIT_Com();
      loc_TaskState_INIT_Adv();
      loc_TaskState_INIT_Noise();
    }
    else
    {
      /* no change profile -> nothing to do here */
    }
  }

  /* lab mode */
  if( (meas_eMeasMode_LAB == loc_AppRtData.RuntimeData.MeasurementMode) ||
      (meas_eMeasMode_APPLAB == loc_AppRtData.RuntimeData.MeasurementMode) )
  {
      lab_TaskState_INIT_Lab();
  }
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Init subfunction Common
 *
 * Initializes all registers for the upcoming measurement and the diagnostic measurement
 * that are common for standard and advanced measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_Com(void)
{
  /*
   * set registers, that are common for standard and advanced measurement
   * -> described in Software Requirements Specification 3.6.2.4
   */
  /* configure dsp -> analog signal processing */
  DSP_ASP_CTRL_bit.g_ana_diag = 0;
  loc_readBackAfterWrite(DSP_ASP_CTRL_bit.g_ana_diag, 0);
    DSP_ASP_CTRL_bit.g_ana      = loc_AppRtData.Parameters.data.GeneralSettings.fields.AnalogGain;
    loc_readBackAfterWrite(DSP_ASP_CTRL_bit.g_ana, loc_AppRtData.Parameters.data.GeneralSettings.fields.AnalogGain);
  DSP_ASP_CTRL_bit.fc_x2      = loc_AppRtData.Parameters.data.GeneralSettings.fields.AnalogLp;
  loc_readBackAfterWrite(DSP_ASP_CTRL_bit.fc_x2, loc_AppRtData.Parameters.data.GeneralSettings.fields.AnalogLp);
  /* configure burst generator */
  uint16_t f_c = 0;
  
    /* compensate of f0 */
    f_c = (loc_AppRtData.Parameters.data.GeneralSettings.fields.SamplingFrequency * FREQUENCY_CORRECTION_VALUE) / Dsi3DrvImp_HWModIfFuns->Get1usClockCfg();
  BRG_BRG_FC_bit.f_c              = f_c;
  loc_readBackAfterWrite(BRG_BRG_FC_bit.f_c, f_c);
  /* configure burst generator -> transducer driver */
  BRG_TDR_CTRL_bit.sel_isrc   = 0;
  loc_readBackAfterWrite(BRG_TDR_CTRL_bit.sel_isrc, 0);
  BRG_TDR_CTRL_bit.i_drv      = loc_AppRtData.Parameters.data.GeneralSettings.fields.TdrCurrent;
  loc_readBackAfterWrite(BRG_TDR_CTRL_bit.i_drv, loc_AppRtData.Parameters.data.GeneralSettings.fields.TdrCurrent);
  /* configure dsp -> ringing frequency measurement */
  DSP_RFM_CTRL_bit.rfm_start  = loc_AppRtData.Parameters.data.GeneralSettings.fields.RingFreqStart;
  loc_readBackAfterWrite(DSP_RFM_CTRL_bit.rfm_start, loc_AppRtData.Parameters.data.GeneralSettings.fields.RingFreqStart);
  DSP_RFM_CTRL_bit.rfm_width  = loc_AppRtData.Parameters.data.GeneralSettings.fields.RingFreqWidth;
  loc_readBackAfterWrite(DSP_RFM_CTRL_bit.rfm_width, loc_AppRtData.Parameters.data.GeneralSettings.fields.RingFreqWidth);
    /* configure dsp -> envelope processor */
    DSP_ENVP_CFG_bit.g_cal      = loc_AppRtData.Parameters.data.GeneralSettings.fields.CalibrationGain;
    loc_readBackAfterWrite(DSP_ENVP_CFG_bit.g_cal, loc_AppRtData.Parameters.data.GeneralSettings.fields.CalibrationGain);
  /* configure DAC */
  DAC_CTRL_CTRL_bit.dac0_cfg   = loc_AppRtData.Parameters.data.GeneralSettings.fields.Dac0Ctrl; 
  loc_readBackAfterWrite(DAC_CTRL_CTRL_bit.dac0_cfg, loc_AppRtData.Parameters.data.GeneralSettings.fields.Dac0Ctrl);
  DAC_CTRL_CTRL_bit.dac1_cfg   = loc_AppRtData.Parameters.data.GeneralSettings.fields.Dac1Ctrl;
  loc_readBackAfterWrite(DAC_CTRL_CTRL_bit.dac1_cfg, loc_AppRtData.Parameters.data.GeneralSettings.fields.Dac1Ctrl);

  /* reset precalculated parameters */
  memset(&preCalculatedStgParam, 0 , sizeof(sPreCalcParam_StgParam_t));
  memset(&preCalculatedStcParam, 0 , sizeof(sPreCalcParam_StcParam_t));
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Init subfunction Standard
 *
 * Initializes all registers for the upcoming measurement and the diagnostic measurement
 * that are specific for standard measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_Std(void)
{
  bool_t execute = true;/*-?|AP5|wladimir.pauls|c2|?*/

  /* get pointer to requested standard profile */
  Meas_uStandardPathProfile* loc_pParam;
  switch(loc_AppRtData.RuntimeData.MeasurementProfile)
  {
  case meas_eMeasProfile_PROFILEA:
    loc_pParam = &(loc_AppRtData.Parameters.data.StandardPathProfileA);
    loc_AppRtData.RuntimeData.TOF_Compensation = (uint16_t)((loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.SPA_TOF_compensation_time)<<5u);
    
    if ( 0u == loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.SPA_meas_time )
    {
      loc_AppRtData.RuntimeData.Meas_time = MEASUREMENT_TIMER_MAX;
    }
    else
    {
      loc_AppRtData.RuntimeData.Meas_time = (uint16_t)((loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.SPA_meas_time)<<8u);
    }
    break;
    
  case meas_eMeasProfile_PROFILEB:
    loc_pParam = &(loc_AppRtData.Parameters.data.StandardPathProfileB);
    loc_AppRtData.RuntimeData.TOF_Compensation = (uint16_t)((loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.SPB_TOF_compensation_time)<<5u);
    
    if ( 0u == loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.SPB_meas_time )
    {
      loc_AppRtData.RuntimeData.Meas_time = MEASUREMENT_TIMER_MAX;
    }
    else
    {
      loc_AppRtData.RuntimeData.Meas_time = (uint16_t)((loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.SPB_meas_time)<<8u);
    }
    
    break;
  case meas_eMeasProfile_PROFILEC:
    loc_pParam = &(loc_AppRtData.Parameters.data.StandardPathProfileC);
    loc_AppRtData.RuntimeData.TOF_Compensation = (uint16_t)((loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.SPC_TOF_compensation_time)<<5u);
    
    if ( 0u == loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.SPC_meas_time )
    {
      loc_AppRtData.RuntimeData.Meas_time = MEASUREMENT_TIMER_MAX;
    }
    else
    {
      loc_AppRtData.RuntimeData.Meas_time = (uint16_t)((loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.SPC_meas_time)<<8u);
    }
    break;
    
  default:
    /* the registers are already in the correct state -> nothing to do here */
    execute = false;
    break;
  }

  if(TRUE == execute)
  {
    /*
     * set registers, that are measurement mode depended
     * -> described in Software Requirements Specification 3.6.2.4
     */
    /* configure burst generator */
    BRG_BRG_CFG_bit.burst_type        = 0;
    loc_readBackAfterWrite(BRG_BRG_CFG_bit.burst_type, 0);
    BRG_BRG_CFG_bit.n_pulses          = loc_pParam->fields.SpxBurstPulses;
    loc_readBackAfterWrite(BRG_BRG_CFG_bit.n_pulses, loc_pParam->fields.SpxBurstPulses);
    uint16_t f_0;
    if(0 != loc_AppRtData.Parameters.data.DsiSettings.fields.SyncFreq)
    {
      /* compensate of f0 */
      f_0 = loc_pParam->fields.SpxBurstFreq * FREQUENCY_CORRECTION_VALUE / Dsi3DrvImp_HWModIfFuns->Get1usClockCfg();
    }
    else
    {
      /* just use standard values */
      f_0 = loc_pParam->fields.SpxBurstFreq;
    }
    BRG_F0_SET(f_0);
    loc_readBackAfterWrite(BRG_F0_GET(), f_0);
    /* configure dsp -> envelope processor */
    DSP_ENVP_CFG_bit.fspi_sel         = 1;
    loc_readBackAfterWrite(DSP_ENVP_CFG_bit.fspi_sel, 1);
    DSP_ENVP_CFG_bit.envp_afc         = 1;
    loc_readBackAfterWrite(DSP_ENVP_CFG_bit.envp_afc, 1);

   
    
      DSP_ENVP_CFG_bit.dsr_sel          = loc_pParam->fields.SpxDs;
      loc_readBackAfterWrite(DSP_ENVP_CFG_bit.dsr_sel, loc_pParam->fields.SpxDs);    
      /* configure dsp -> fast time constant module */
      DSP_FTC_CTRL_bit.ftc_en           = loc_pParam->fields.SpxFtcEn;
      loc_readBackAfterWrite(DSP_FTC_CTRL_bit.ftc_en, loc_pParam->fields.SpxFtcEn);
      DSP_FTC_CTRL_bit.ftc_cfg          = loc_pParam->fields.SpxFtcCfg;
      loc_readBackAfterWrite(DSP_FTC_CTRL_bit.ftc_cfg, loc_pParam->fields.SpxFtcCfg);
    
       /* configure dsp -> sensitivity time control */
      DSP_STC_CTRL_bit.ampd_stc_mod     = loc_pParam->fields.SpxStcMod;
      loc_readBackAfterWrite(DSP_STC_CTRL_bit.ampd_stc_mod, loc_pParam->fields.SpxStcMod);
      DSP_STC_CTRL_bit.ampd_g_dig_target= loc_pParam->fields.SpxMeasGain;
      loc_readBackAfterWrite(DSP_STC_CTRL_bit.ampd_g_dig_target, loc_pParam->fields.SpxMeasGain);
      DSP_STC_TB_bit.ampd_stc_tb        = loc_pParam->fields.SpxStcTb;
      loc_readBackAfterWrite(DSP_STC_TB_bit.ampd_stc_tb, loc_pParam->fields.SpxStcTb);
      
      /* configure dsp -> automatic threshold generator */
      DSP_ATG_CTRL_bit.atg_cfg          = loc_pParam->fields.SpxAtgCfg;
      loc_readBackAfterWrite(DSP_ATG_CTRL_bit.atg_cfg, loc_pParam->fields.SpxAtgCfg);
      DSP_ATG_CTRL_bit.atg_ini          = loc_pParam->fields.SpxAtgIni;
      loc_readBackAfterWrite(DSP_ATG_CTRL_bit.atg_ini, loc_pParam->fields.SpxAtgIni);
      DSP_ATG_CTRL_bit.atg_alpha        = loc_pParam->fields.SpxAtgAlpha;
      loc_readBackAfterWrite(DSP_ATG_CTRL_bit.atg_alpha, loc_pParam->fields.SpxAtgAlpha);
      DSP_ATG_CTRL_bit.atg_tau          = loc_pParam->fields.SpxAtgTau;
      loc_readBackAfterWrite(DSP_ATG_CTRL_bit.atg_tau, loc_pParam->fields.SpxAtgTau);
      
      /* configure dsp -> echo evaluation SpxEevalSens */
      DSP_EEVAL_CTRL_SENSITIVITY_SET(loc_pParam->fields.SpxEevalSens);
      loc_readBackAfterWrite(DSP_EEVAL_CTRL_SENSITIVITY_GET(), loc_pParam->fields.SpxEevalSens);

    DSP_EEVAL_CTRL_bit.eeval_dma_val  = loc_pParam->fields.SpxEevalVal;
    loc_readBackAfterWrite(DSP_EEVAL_CTRL_bit.eeval_dma_val, loc_pParam->fields.SpxEevalVal);
    DSP_EEVAL_CTRL_SOURCE_SELECT_SET(loc_pParam->fields.SpxEevalSel);
    loc_readBackAfterWrite(DSP_EEVAL_CTRL_SOURCE_SELECT_GET(), loc_pParam->fields.SpxEevalSel);
  }
  else
  {
    /* nothing to do here */
  }
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Init subfunction Advanced
 *
 * Initializes all registers for the upcoming measurement and the diagnostic measurement
 * that are specific for advanced measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_Adv(void)
{
  bool_t execute = true;/*-?|AP5|wladimir.pauls|c3|?*/

  /* get pointer to requested advanced profile */
  Meas_uAdvancedPathProfile* loc_pParam;
  switch(loc_AppRtData.RuntimeData.MeasurementProfile)
  {
  case meas_eMeasProfile_PROFILEA:
    loc_pParam = &(loc_AppRtData.Parameters.data.AdvancedPathProfileA);
    loc_AppRtData.RuntimeData.TOF_Compensation = (uint16_t)((loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.APA_TOF_compensation_time)<<5u);
    
    if ( 0u == loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.APA_meas_time )
    {
      loc_AppRtData.RuntimeData.Meas_time = MEASUREMENT_TIMER_MAX;
    }
    else
    {
      loc_AppRtData.RuntimeData.Meas_time = (uint16_t)((loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.APA_meas_time)<<8u);
    }
    break;
  case meas_eMeasProfile_PROFILEB:
    loc_pParam = &(loc_AppRtData.Parameters.data.AdvancedPathProfileB);
    loc_AppRtData.RuntimeData.TOF_Compensation = (uint16_t)((loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.APB_TOF_compensation_time)<<5u);
    
    if ( 0u == loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.APB_meas_time )
    {
      loc_AppRtData.RuntimeData.Meas_time = MEASUREMENT_TIMER_MAX;
    }
    else
    {
      loc_AppRtData.RuntimeData.Meas_time = (uint16_t)((loc_AppRtData.Parameters.data.TimeOfFlightCompensation.fields.APB_meas_time)<<8u);
    }
    break;
  case meas_eMeasProfile_PROFILEC:
    /* in advanced mode, meas_eMeasProfile_PROFILEC is equivalent to meas_eMeasProfile_NOCHANGE */
  default:
    /* meas_eMeasProfile_NOCHANGE */
    /* the registers are already in the correct state -> nothing to do here */
    execute = false;
    break;
  }


  if(true == execute)
  {
    /* set data for dsi3 layer */
    loc_AppRtData.RuntimeData.MinConf = loc_pParam->fields.ApxMinConf;

    /*
     * set registers, that are measurement mode depended
     * -> described in Software Requirements Specification 3.6.2.4
     */
    /* configure burst generator */
    BRG_BRG_CFG_bit.burst_type          = 1;
    loc_readBackAfterWrite(BRG_BRG_CFG_bit.burst_type, 1);

    uint16_t f_0;
    uint16_t f_1;
    if(0 != loc_AppRtData.Parameters.data.DsiSettings.fields.SyncFreq)
    {
      /* compensate of f0 */
      f_0 = loc_pParam->fields.ApxBurstFreqLo * FREQUENCY_CORRECTION_VALUE / Dsi3DrvImp_HWModIfFuns->Get1usClockCfg();
      f_1 = loc_pParam->fields.ApxBurstFreqHi * FREQUENCY_CORRECTION_VALUE / Dsi3DrvImp_HWModIfFuns->Get1usClockCfg();
    }
    else
    {
      /* just use standard values */
      f_0 = loc_pParam->fields.ApxBurstFreqLo;
      f_1 = loc_pParam->fields.ApxBurstFreqHi;
    }
    BRG_BRG_F0_bit.f_0              = f_0;
    loc_readBackAfterWrite(BRG_BRG_F0_bit.f_0, f_0);
    BRG_BRG_F1_bit.f_1              = f_1;
    loc_readBackAfterWrite(BRG_BRG_F1_bit.f_1, f_1);
    
    /* configure dsp -> envelope processor */
    DSP_ENVP_CFG_bit.aspi_sel           = 0;
    loc_readBackAfterWrite(DSP_ENVP_CFG_bit.aspi_sel, 0);
    DSP_ENVP_FILT_CFG_bit.f1_coeff_sel  = 0;
    loc_readBackAfterWrite(DSP_ENVP_FILT_CFG_bit.f1_coeff_sel, 0);
    DSP_ENVP_FILT_CFG_bit.f2_coeff_sel  = 0;
    loc_readBackAfterWrite(DSP_ENVP_FILT_CFG_bit.f2_coeff_sel, 0);

      
      /* configure burst generator part 2 */
      BRG_BRG_CFG_bit.n_pulses            = loc_pParam->fields.ApxBurstPulses;
      loc_readBackAfterWrite(BRG_BRG_CFG_bit.n_pulses, loc_pParam->fields.ApxBurstPulses);
      BRG_BRG_CFG_bit.code_len            = loc_pParam->fields.ApxCodeLength;
      loc_readBackAfterWrite(BRG_BRG_CFG_bit.code_len, loc_pParam->fields.ApxCodeLength);
      BRG_BRG_FDELTA_bit.f_delta          = loc_pParam->fields.ApxBurstFreqDelta;
      loc_readBackAfterWrite(BRG_BRG_FDELTA_bit.f_delta, loc_pParam->fields.ApxBurstFreqDelta);
       
      /* configure dsp -> downsampling and filter length */
      DSP_ENVP_CFG_bit.dsr_sel            = loc_pParam->fields.ApxDs;
      loc_readBackAfterWrite(DSP_ENVP_CFG_bit.dsr_sel, loc_pParam->fields.ApxDs);
      DSP_ENVP_FILT_CFG_bit.filt_len_code = loc_pParam->fields.ApxFilterLength;
      loc_readBackAfterWrite(DSP_ENVP_FILT_CFG_bit.filt_len_code, loc_pParam->fields.ApxFilterLength);
      
      /* configure dsp -> filter coefficients */
      DSP_ENVP_COEFF_3_2_1_0_bit.coeff    = loc_pParam->fields.ApxEnvpCoeff3_0;
      loc_readBackAfterWrite(DSP_ENVP_COEFF_3_2_1_0_bit.coeff, loc_pParam->fields.ApxEnvpCoeff3_0);
      DSP_ENVP_COEFF_7_6_5_4_bit.coeff    = loc_pParam->fields.ApxEnvpCoeff7_4;
      loc_readBackAfterWrite(DSP_ENVP_COEFF_7_6_5_4_bit.coeff, loc_pParam->fields.ApxEnvpCoeff7_4);
      DSP_ENVP_COEFF_11_10_9_8_bit.coeff  = loc_pParam->fields.ApxEnvpCoeff11_8;
      loc_readBackAfterWrite(DSP_ENVP_COEFF_11_10_9_8_bit.coeff, loc_pParam->fields.ApxEnvpCoeff11_8);
      DSP_ENVP_COEFF_15_14_13_12_bit.coeff= loc_pParam->fields.ApxEnvpCoeff15_12;
      loc_readBackAfterWrite(DSP_ENVP_COEFF_15_14_13_12_bit.coeff, loc_pParam->fields.ApxEnvpCoeff15_12);
      DSP_ENVP_COEFF_19_18_17_16_bit.coeff= loc_pParam->fields.ApxEnvpCoeff19_16;
      loc_readBackAfterWrite(DSP_ENVP_COEFF_19_18_17_16_bit.coeff, loc_pParam->fields.ApxEnvpCoeff19_16);
      DSP_ENVP_COEFF_23_22_21_20_bit.coeff= loc_pParam->fields.ApxEnvpCoeff23_20;
      loc_readBackAfterWrite(DSP_ENVP_COEFF_23_22_21_20_bit.coeff, loc_pParam->fields.ApxEnvpCoeff23_20);
      DSP_ENVP_COEFF_27_26_25_24_bit.coeff= loc_pParam->fields.ApxEnvpCoeff27_24;
      loc_readBackAfterWrite(DSP_ENVP_COEFF_27_26_25_24_bit.coeff, loc_pParam->fields.ApxEnvpCoeff27_24);
      DSP_ENVP_COEFF_31_30_29_28_bit.coeff= loc_pParam->fields.ApxEnvpCoeff31_28;
      loc_readBackAfterWrite(DSP_ENVP_COEFF_31_30_29_28_bit.coeff, loc_pParam->fields.ApxEnvpCoeff31_28);  
      
      /* configure dsp -> advanced automatic threshold generator */
      DSP_AATG1_CTRL_bit.aatg1_off        = loc_pParam->fields.ApxAatgOff;
      loc_readBackAfterWrite(DSP_AATG1_CTRL_bit.aatg1_off, loc_pParam->fields.ApxAatgOff);
      DSP_AATG1_CTRL_bit.aatg1_alpha      = loc_pParam->fields.ApxAatgAlpha;
      loc_readBackAfterWrite(DSP_AATG1_CTRL_bit.aatg1_alpha, loc_pParam->fields.ApxAatgAlpha);
      DSP_AATG1_CTRL_bit.aatg1_cw         = loc_pParam->fields.ApxAatgCw;
      loc_readBackAfterWrite(DSP_AATG1_CTRL_bit.aatg1_cw, loc_pParam->fields.ApxAatgCw);
      DSP_AATG1_CTRL_bit.aatg1_cn         = loc_pParam->fields.ApxAatgCn;
      loc_readBackAfterWrite(DSP_AATG1_CTRL_bit.aatg1_cn, loc_pParam->fields.ApxAatgCn);
      DSP_AATG2_CTRL_bit.aatg2_off        = loc_pParam->fields.ApxAatgOff;
      loc_readBackAfterWrite(DSP_AATG2_CTRL_bit.aatg2_off, loc_pParam->fields.ApxAatgOff);
      DSP_AATG2_CTRL_bit.aatg2_alpha      = loc_pParam->fields.ApxAatgAlpha;
      loc_readBackAfterWrite(DSP_AATG2_CTRL_bit.aatg2_alpha, loc_pParam->fields.ApxAatgAlpha);
      DSP_AATG2_CTRL_bit.aatg2_cw         = loc_pParam->fields.ApxAatgCw;
      loc_readBackAfterWrite(DSP_AATG2_CTRL_bit.aatg2_cw, loc_pParam->fields.ApxAatgCw);
      DSP_AATG2_CTRL_bit.aatg2_cn         = loc_pParam->fields.ApxAatgCn;
      loc_readBackAfterWrite(DSP_AATG2_CTRL_bit.aatg2_cn, loc_pParam->fields.ApxAatgCn);
      
      /* configure dsp -> echo evaluation */
      DSP_EEVAL_CTRL_bit.eeval_sens       = loc_pParam->fields.ApxEevalSens;
      loc_readBackAfterWrite(DSP_EEVAL_CTRL_bit.eeval_sens, loc_pParam->fields.ApxEevalSens);
      

  }
  else
  {
    /* nothing to do here */
  }
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Init subfunction Noise
 *
 * Initializes all registers for the upcoming measurement and the diagnostic measurement
 * that are specific for noise measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_Noise(void)
{
    /* set digital gain to be constant */
  DSP_STC_CTRL_STC_TB_SET(0u);
  
  /* set registers for the noise measurement */
  DSP_ENVP_CFG_bit.envp_cfg     = loc_AppRtData.Parameters.data.NoiseMeasurement.fields.NoiseMeasFilterBw;
  loc_readBackAfterWrite(DSP_ENVP_CFG_bit.envp_cfg, loc_AppRtData.Parameters.data.NoiseMeasurement.fields.NoiseMeasFilterBw);
 
    DSP_AMPD_CTRL_bit.ampd_g_dig  = loc_AppRtData.Parameters.data.NoiseMeasurement.fields.NoiseMeasGain;
    loc_readBackAfterWrite(DSP_AMPD_CTRL_bit.ampd_g_dig, loc_AppRtData.Parameters.data.NoiseMeasurement.fields.NoiseMeasGain); 
  /* Switch DSP on */
  DSP_CTRL_DSP_ON();

  /* Burst length for start of noise measurement is zero to start receive-only mode */
  BRG_BRG_CFG_bit.n_pulses = 0;
  loc_readBackAfterWrite(BRG_BRG_CFG_bit.n_pulses, 0);

  /* Set threshold to noise threshold without a change step */
  DSP_STG_TH_SET(loc_AppRtData.Parameters.data.NoiseMeasurement.fields.NoiseMeasThreshold);
  DSP_STG_STEP_SET(0u);
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Init subfunction Noise
 *
 * Initializes all registers for the upcoming measurement and the diagnostic measurement
 * that are specific for noise measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_NOISE_MEAS(void)
{
  bool_t measFinished = app_NoiseMeasurement(&loc_AppRtData);
  if(TRUE == measFinished)
  {
    /* disable the timer for noise measurement */
    SWT_IRQ_DISABLE(swtimer_IRQ_EVT_CNT_ZERO_TickPeriodTimer);
    SWT_CTRL_IRQ_CLEAR(swtimer_IRQ_EVT_CNT_ZERO_TickPeriodTimer);
    SWT_DISABLE(swtimer_eTickPeriodTimer);

    /* switch to next state -> init echo meas state */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_INIT_ECHO_MEAS;
  }
  else
  {
    /* nothing to do here */
  }
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Initialize Echo Measurement
 *
 * Initializes all registers for the upcoming measurement
 * that have been modified for the noise measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_ECHO_MEAS(void)
{
  /* set registers for echo measurement, that have been changed for noise measurement */
  if(meas_eMeasKind_STANDARD == loc_AppRtData.RuntimeData.MeasurementKind)
  {
    /* standard measurement */
    loc_TaskState_INIT_ECHO_MEAS_Std();
  }
  else
  {
    /* advanced measurement */
    loc_TaskState_INIT_ECHO_MEAS_Adv();
  }
  /* initiate near field detection */
  loc_TaskState_INIT_ECHO_MEAS_Nfd();
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Initialize Echo Measurement subfunction Standard
 *
 * Initializes all registers for the upcoming measurement
 * that have been modified for the noise measurement
 * which are specific for standard measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_ECHO_MEAS_Std(void)
{
  bool_t execute = TRUE;/*-?|AP5|wladimir.pauls|c4|?*/

  /* get pointer to requested standard profile */
  Meas_uStandardPathProfile* loc_pParam;
  switch(loc_AppRtData.RuntimeData.MeasurementProfile)
  {
  case meas_eMeasProfile_PROFILEA:
    loc_pParam = &(loc_AppRtData.Parameters.data.StandardPathProfileA);
    break;
  case meas_eMeasProfile_PROFILEB:
    loc_pParam = &(loc_AppRtData.Parameters.data.StandardPathProfileB);
    break;
  case meas_eMeasProfile_PROFILEC:
    loc_pParam = &(loc_AppRtData.Parameters.data.StandardPathProfileC);
    break;
  default:
    /* meas_eMeasProfile_NOCHANGE */
    /* the registers are already in the correct state -> nothing to do here */
    execute = FALSE;
    break;
  }

  if(TRUE == execute)
  {
    /* set register, that have been changed for noise measurement */
    BRG_BRG_CFG_bit.n_pulses      = loc_pParam->fields.SpxBurstPulses;
    loc_readBackAfterWrite(BRG_BRG_CFG_bit.n_pulses, loc_pParam->fields.SpxBurstPulses);
    DSP_ENVP_CFG_bit.envp_cfg     = loc_pParam->fields.SpxMeasFilterBw;
    loc_readBackAfterWrite(DSP_ENVP_CFG_bit.envp_cfg, loc_pParam->fields.SpxMeasFilterBw);

      DSP_AMPD_CTRL_bit.ampd_g_dig  = loc_pParam->fields.SpxMeasGain;
      loc_readBackAfterWrite(DSP_AMPD_CTRL_bit.ampd_g_dig, loc_pParam->fields.SpxMeasGain);
    
    /* set initial static threshold values */
    DSP_STG_TH_SET(loc_pParam->fields.SpxStgHeight1);
    DSP_STG_STEP_SET(0u);
    /* pre calculate stg values for critical process whilst echo meas */
    loc_TaskState_PreCalcParam_INIT_ECHO_MEAS_Std(loc_pParam);

    /* match register modifications defined by the requirements */
    /* if Filter BW = 0, chose bw according to table "bandwidth of envelope processor" in datasheet */
    if(BURST_CNT_0 == loc_pParam->fields.SpxMeasFilterBw)
    {
      if(BURST_CNT_8 > loc_pParam->fields.SpxBurstPulses)
      {
        DSP_ENVP_CFG_bit.envp_cfg = ENVP_CFG_BW_4;
        loc_readBackAfterWrite(DSP_ENVP_CFG_bit.envp_cfg, ENVP_CFG_BW_4);
      }
      else
      {
        if(BURST_CNT_28 > loc_pParam->fields.SpxBurstPulses)
        {
          DSP_ENVP_CFG_bit.envp_cfg = ENVP_CFG_BW_5;
          loc_readBackAfterWrite(DSP_ENVP_CFG_bit.envp_cfg, ENVP_CFG_BW_5);
        }
        else
        {
          DSP_ENVP_CFG_bit.envp_cfg = ENVP_CFG_BW_6;
          loc_readBackAfterWrite(DSP_ENVP_CFG_bit.envp_cfg, ENVP_CFG_BW_6);
        }
      }
    }
    else
    {
      /* no use atm */
    }

    /* handle the different measurement configurations */
    switch(loc_AppRtData.RuntimeData.MeasurementConf)
    {
    case meas_eMeasConf_DIRECT:
    case meas_eMeasConf_DIRECT_INV:
      /* set masking time */
      loc_AppRtData.RuntimeData.MaskingTime = (loc_pParam->fields.SpxMeasMaskDirect) + (loc_AppRtData.RuntimeData.TOF_Compensation>>5); /* SMA52417-106 */
      break;
    case meas_eMeasConf_INDIRECT:
      /* disable burst */
      BRG_BRG_CFG_bit.n_pulses            = 0;
      loc_readBackAfterWrite(BRG_BRG_CFG_bit.n_pulses, 0);
      /* set masking time */
      loc_AppRtData.RuntimeData.MaskingTime = (loc_pParam->fields.SpxMeasMaskIndirect) + (loc_AppRtData.RuntimeData.TOF_Compensation>>5); /* SMA52417-106 */
      break;
    default:
      /* meas_eMeasConf_NONE should be impossible at this point */
      break;
    }
  }
  else
  {
    /* profile is NOCHANGE -> nothing to do here */
  }
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Initialize Echo Measurement subfunction Standard
 *
 * Precalculates all standard measurement related parameters
 *
 * @param       loc_pParam      Pointer to std meas parameter struct
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_PreCalcParam_INIT_ECHO_MEAS_Std(Meas_uStandardPathProfile* loc_pParam)
{
  /* calc stc parameters */
  preCalculatedStcParam.StcGain = loc_pParam->fields.SpxStcGain;
  preCalculatedStcParam.StcMod = loc_pParam->fields.SpxStcMod;
  preCalculatedStcParam.StcStart = loc_pParam->fields.SpxStcStart;
  preCalculatedStcParam.StcTb = loc_pParam->fields.SpxStcTb;

  /* calc stg intervals */
  preCalculatedStgParam.Interval1 = loc_pParam->fields.SpxStgInterval1;
  preCalculatedStgParam.Interval2 = preCalculatedStgParam.Interval1 + loc_pParam->fields.SpxStgInterval2;
  preCalculatedStgParam.Interval3 = preCalculatedStgParam.Interval2 + loc_pParam->fields.SpxStgInterval3;
  preCalculatedStgParam.Interval4 = preCalculatedStgParam.Interval3 + loc_pParam->fields.SpxStgInterval4;

  /* calc stg parameters for interval 2 */
   if(loc_pParam->fields.SpxStgHeight2 > loc_pParam->fields.SpxStgHeight1)
   {
     /* STG curve has positive gradient in this period */
     preCalculatedStgParam.Gradient1 = STG_POSITIVE_CURVE_GRADIENT;
     /* in case of timing problems: could be precalculated in initialization */
     preCalculatedStgParam.TimeBase1 = (uint16_t)((uint32_t)(loc_pParam->fields.SpxStgInterval2 * ECHO_MEASUREMENT_MONITORING_PERIOD) / (uint16_t)(loc_pParam->fields.SpxStgHeight2 - loc_pParam->fields.SpxStgHeight1));
   }
   else
   {
     if(loc_pParam->fields.SpxStgHeight2 < loc_pParam->fields.SpxStgHeight1)
     {
       /* STG curve has positive gradient in this period */
       /* rule suppression: this cast is because of signed register value of STG_STEP */
       /* PRQA S 2895 1 */
       preCalculatedStgParam.Gradient1 = STG_NEGATIVE_CURVE_GRADIENT;
       /* in case of timing problems: could be precalculated in initialization */
       preCalculatedStgParam.TimeBase1 = (uint16_t)((uint32_t)(loc_pParam->fields.SpxStgInterval2 * ECHO_MEASUREMENT_MONITORING_PERIOD) / (uint16_t)(loc_pParam->fields.SpxStgHeight1 - loc_pParam->fields.SpxStgHeight2));
     }
     else
     {
       /* no change in this interval */
       preCalculatedStgParam.Gradient1 = 0u;
       preCalculatedStgParam.TimeBase1 = 0u;
     }
   }

   /* calc stg parameters for interval 3 */
   if(loc_pParam->fields.SpxStgHeight3 > loc_pParam->fields.SpxStgHeight2)
   {
     /* STG curve has positive gradient in this period */
     preCalculatedStgParam.Gradient2 = STG_POSITIVE_CURVE_GRADIENT;
     /* in case of timing problems: could be precalculated in initialization */
     preCalculatedStgParam.TimeBase2 = (uint16_t)((uint32_t)(loc_pParam->fields.SpxStgInterval3 * ECHO_MEASUREMENT_MONITORING_PERIOD) / (uint16_t)(loc_pParam->fields.SpxStgHeight3 - loc_pParam->fields.SpxStgHeight2)); 
   }
   else
   {
     if(loc_pParam->fields.SpxStgHeight3 < loc_pParam->fields.SpxStgHeight2)
     {
       /* STG curve has positive gradient in this period */
       /* rule suppression: this cast is because of signed register value of STG_STEP */
       /* PRQA S 2895 1 */
       preCalculatedStgParam.Gradient2 = STG_NEGATIVE_CURVE_GRADIENT;
       /* in case of timing problems: could be precalculated in initialization */
       preCalculatedStgParam.TimeBase2 = (uint16_t)((uint32_t)(loc_pParam->fields.SpxStgInterval3 * ECHO_MEASUREMENT_MONITORING_PERIOD) /(uint16_t)(loc_pParam->fields.SpxStgHeight2 - loc_pParam->fields.SpxStgHeight3));
     }
     else
     {
       /* no change in this interval */
       preCalculatedStgParam.Gradient2 = 0u;
       preCalculatedStgParam.TimeBase2 = 0u;
     }
   }

   /* calc stg parameters for interval 4 */
   if(loc_pParam->fields.SpxStgHeight4 > loc_pParam->fields.SpxStgHeight3)
   {
     /* STG curve has positive gradient in this period */
     preCalculatedStgParam.Gradient3 = STG_POSITIVE_CURVE_GRADIENT;
     /* in case of timing problems: could be precalculated in initialization */
     preCalculatedStgParam.TimeBase3 = (uint16_t)((uint32_t)(loc_pParam->fields.SpxStgInterval4 * ECHO_MEASUREMENT_MONITORING_PERIOD) / (uint16_t)(loc_pParam->fields.SpxStgHeight4 - loc_pParam->fields.SpxStgHeight3));
   }
   else
   {
     if(loc_pParam->fields.SpxStgHeight4 < loc_pParam->fields.SpxStgHeight3)
     {
       /* STG curve has positive gradient in this period */
       /* rule suppression: this cast is because of signed register value of STG_STEP */
       /* PRQA S 2895 1 */
       preCalculatedStgParam.Gradient3 = STG_NEGATIVE_CURVE_GRADIENT;
       /* in case of timing problems: could be precalculated in initialization */
       preCalculatedStgParam.TimeBase3 = (uint16_t)((uint32_t)(loc_pParam->fields.SpxStgInterval4 * ECHO_MEASUREMENT_MONITORING_PERIOD) / (uint16_t)(loc_pParam->fields.SpxStgHeight3 - loc_pParam->fields.SpxStgHeight4));
     }
     else
     {
       /* no change in this interval */
       preCalculatedStgParam.Gradient3 = 0;
       preCalculatedStgParam.TimeBase3 = 0;
     }
   }
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Initialize Echo Measurement subfunction Advanced
 *
 * Initializes all registers for the upcoming measurement
 * that have been modified for the noise measurement
 * which are specific for advanced measurement
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_INIT_ECHO_MEAS_Adv(void)
{
  bool_t execute = TRUE;/*-?|AP5|wladimir.pauls|c5|?*/

  /* get pointer to requested advanced profile */
  Meas_uAdvancedPathProfile* loc_pParam;
  switch(loc_AppRtData.RuntimeData.MeasurementProfile)
  {
  case meas_eMeasProfile_PROFILEA:
    loc_pParam = &(loc_AppRtData.Parameters.data.AdvancedPathProfileA);
    break;
  case meas_eMeasProfile_PROFILEB:
    loc_pParam = &(loc_AppRtData.Parameters.data.AdvancedPathProfileB);
    break;
  case meas_eMeasProfile_PROFILEC:
    /* in advanced mode, meas_eMeasProfile_PROFILEC is equivalent to meas_eMeasProfile_NOCHANGE */
  default:
    /* meas_eMeasProfile_NOCHANGE */
    /* the registers are already in the correct state -> nothing to do here */
    execute = FALSE;
    break;
  }

  if(TRUE == execute)
  {
    /* set register, that have been changed for noise measurement */
    BRG_BRG_CFG_bit.n_pulses            = loc_pParam->fields.ApxBurstPulses;
    loc_readBackAfterWrite(BRG_BRG_CFG_bit.n_pulses, loc_pParam->fields.ApxBurstPulses);

    /* handle the different measurement configurations */
    switch(loc_AppRtData.RuntimeData.MeasurementConf)
    {
    case meas_eMeasConf_DIRECT:     /* chirp up */
      BRG_BRG_CODE_bit.code               = loc_pParam->fields.ApxCode;
      loc_readBackAfterWrite(BRG_BRG_CODE_bit.code, loc_pParam->fields.ApxCode);
      /* set masking time */
      loc_AppRtData.RuntimeData.MaskingTime = (loc_pParam->fields.ApxMeasMaskDirect) + (loc_AppRtData.RuntimeData.TOF_Compensation>>5); 
      break;
    case meas_eMeasConf_DIRECT_INV: /* chirp up inverted */
      BRG_BRG_CODE_bit.code               = ~(uint32_t)loc_pParam->fields.ApxCode;
      loc_readBackAfterWrite(BRG_BRG_CODE_bit.code, ~(uint32_t)loc_pParam->fields.ApxCode);
      /* set masking time */
      loc_AppRtData.RuntimeData.MaskingTime = (loc_pParam->fields.ApxMeasMaskDirect) + (loc_AppRtData.RuntimeData.TOF_Compensation>>5); 
      break;
    case meas_eMeasConf_INDIRECT:   /* indirect measurement */
      /* disable burst */
      BRG_BRG_CFG_bit.n_pulses            = 0;
      loc_readBackAfterWrite(BRG_BRG_CFG_bit.n_pulses, 0);
      /* set masking time */
      loc_AppRtData.RuntimeData.MaskingTime = (loc_pParam->fields.ApxMeasMaskIndirect) + (loc_AppRtData.RuntimeData.TOF_Compensation>>5); 
      break;
    default:
      /* meas_eMeasConf_NONE should be impossible at this point */
      break;
    }
  }
  else
  {
    /* profile is NOCHANGE -> nothing to do here */
  }
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Initialize Echo Measurement subfunction Near field detection
 *
 * Initializes all registers for the upcoming near field detection
 *
 * @return      void            None.
 * ****************************************************************************/
void loc_TaskState_INIT_ECHO_MEAS_Nfd(void)
{
  /* configure registers for NFD */
  DSP_NFD_CTRL_IRQ_SET(loc_AppRtData.Parameters.data.NfdSettings.fields.NfdCtrlIrq);
  loc_readBackAfterWrite(DSP_NFD_CTRL_IRQ_GET(), loc_AppRtData.Parameters.data.NfdSettings.fields.NfdCtrlIrq);
  DSP_NFD_CTRL_EVALSENS_SET(loc_AppRtData.Parameters.data.NfdSettings.fields.NfdCtrlSens);
  loc_readBackAfterWrite(DSP_NFD_CTRL_EVALSENS_GET(), loc_AppRtData.Parameters.data.NfdSettings.fields.NfdCtrlSens);
  DSP_NFD_TH_bit.nfd_th = loc_AppRtData.Parameters.data.NfdSettings.fields.NfdThreshold;
  loc_readBackAfterWrite(DSP_NFD_TH_bit.nfd_th, loc_AppRtData.Parameters.data.NfdSettings.fields.NfdThreshold);
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Echo Measurement asynchronous
 *
 * Runs echo measurement related controlling tasks in the main loop
 *
 * SM20: VTANK Overvoltage (Part 1 of 1) Both chapters are realized via the same function.
 * (for details see SafetyManual)
 *
 * @return      void            None.
 * ****************************************************************************/
void loc_TaskState_ECHO_MEAS_async(void)
{
  /* check if the hardware measurement timer has reached its maximum or measuremend length */
  if( (MEASUREMENT_TIMER_MAX <= DSP_MT_bit.mt_ts) || (loc_AppRtData.RuntimeData.Meas_time <= DSP_MT_bit.mt_ts) )
  {
    /* The measurement has ended. Trigger the de-initialization phase */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_POST_MEAS;
  }
  else
  {
    /* in case of direct measurement, perform additional tasks */
    if(meas_eMeasConf_INDIRECT != loc_AppRtData.RuntimeData.MeasurementConf)
    {
      /* check if burst phase is still running */
      if(BRG_STATUS_BURST_RUNNING == BRG_BRG_CTRL_bit.burst_sta)
      {
        /* driver voltage monitoring - VTANK over voltage (async) */
        if( (BRG_TDR_STATUS & BITMASK_OVER_VOLTAGE_AT_VTANK_DURING_BURST) != 0u )
        {
          /* Hardware malfunction occured -> set HwErr Flag */
          err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_OVER_VOLTAGE_AT_VTANK_DURING_BURST);
        }
        else
        {
          /* everything ok -> nothing to do here */
        }
        /* Vtank monitor (async) */
        app_VtankMonitoring(&loc_AppRtData);
      }
      else
      {
        /* if hardware malfunction occured -> set HwErr Flag */
        loc_check_TdrStat();
        
        /* burst phase is over -> indicate, that Burst Monitoring has finished */
        loc_AppRtData.Results.BurstMonitoring.AccquisitionFinished = TRUE;
      }
      /* Burst status (sync) */
      /* Driver default states */

      /* Ringing frequency / time measurement (async) */
      app_RingingBehaviour(&loc_AppRtData);
    }
    else
    {
      /* Added to satisfy the coding rules. */
    }

    /* Noise measurement during echo detection (sync) */
  }
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Echo Measurement Manage STC and STG
 *
 * sets sensitivity time control registers at its start point and
 * changes static threshold generation registers over time
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_ECHO_MEAS_manage_stc_and_stg(void)
{
  /* change stg registers over time*/
  if(preCalculatedStcParam.StcStart == loc_AppRtData.Results.MeasurementTime)
  {
    /* set stc register at start time */
    DSP_STC_CTRL_bit.ampd_stc_mod     = preCalculatedStcParam.StcMod;
    DSP_STC_CTRL_bit.ampd_g_dig_target= preCalculatedStcParam.StcGain;
    DSP_STC_TB_bit.ampd_stc_tb        = preCalculatedStcParam.StcTb;
  }
  /* 18/05/02/jlue: changed logic from "else if" to "if" to be able to set stc and stg in one time step */ 
  if (preCalculatedStgParam.Interval1 == loc_AppRtData.Results.MeasurementTime)
  {
   /* set curve gradient */
   DSP_STG_STEP_SET(preCalculatedStgParam.Gradient1);
   DSP_STG_TB_SET(preCalculatedStgParam.TimeBase1);
  }
  else if(preCalculatedStgParam.Interval2 == loc_AppRtData.Results.MeasurementTime)
  {
   /* set curve gradient */
   DSP_STG_STEP_SET(preCalculatedStgParam.Gradient2);
   DSP_STG_TB_SET(preCalculatedStgParam.TimeBase2);
  }
  else if(preCalculatedStgParam.Interval3 == loc_AppRtData.Results.MeasurementTime)
  {
   /* set curve gradient */
   DSP_STG_STEP_SET(preCalculatedStgParam.Gradient3);
   DSP_STG_TB_SET(preCalculatedStgParam.TimeBase3);
  }
  else if(preCalculatedStgParam.Interval4 == loc_AppRtData.Results.MeasurementTime)
  {
   /* set curve gradient */
   DSP_STG_STEP_SET(0u);
   DSP_STG_TB_SET(0u);
  }
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Echo Measurement synchronous
 *
 * Runs echo measurement related controlling tasks, triggered by the tick timer
 *
 * SM10: Burst status 
 * (for details see SafetyManual)
 *
 * SM13: Driver default states
 * (for details see SafetyManual)
 *
 * SM31: Noise Measurement (during)
 * (for details see SafetyManual)
 *
 * @return      void             None.
 * ****************************************************************************/
void loc_TaskState_ECHO_MEAS_sync(void)
{
  /* check if measurement timer has reached its maximum or measuremend length */
  if( (MEASUREMENT_TIMER_MAX <= DSP_MT_bit.mt_ts) || (loc_AppRtData.RuntimeData.Meas_time <= DSP_MT_bit.mt_ts) )
  {
    loc_AppRtData.CurrentState = meas_eMeas_STATE_POST_MEAS;
  }
  else
  {
    /* in case of direct measurement, perform additional tasks */
    if(meas_eMeasConf_INDIRECT != loc_AppRtData.RuntimeData.MeasurementConf)
    {
      /* Burst status (sync) */
      if(BRG_STATUS_BURST_RUNNING == BRG_BRG_CTRL_bit.burst_sta)
      {
        loc_AppRtData.Results.BurstMonitoring.BurstLength++;
      }
      else
      { /* no burst running -> do not increment burst length */
        /* set driver default states */
        BRG_BRG_CFG_bit.n_pulses = 0; /* see SM13 */
      }
      /* driver voltage monitoring - VTANK over voltage in (async)*/
      /* VSUP monitor (async) */
      /* Ringing frequency measurement - Ringing behavior (async) */
      /* Ringing frequency measurement - ringing time measurement (async) */
    }
    else
    {
      /* Added to satisfy the coding rules. */
    }

    /* Noise measurement during echo detection (sync) */ 
    if((loc_AppRtData.Results.MeasurementTime & ECHO_MEASUREMENT_NOISE_MONITORING_PERIOD) == ECHO_MEASUREMENT_NOISE_MONITORING_PERIOD)
    {
      /* get sample */ // ReHu: What is the sample? See questions above in the header.
      /* Only use upper 6 bits representing the current voltage level.*/
      uint32_t sample = DSP_ATG_TH_bit.atg_th >> 2;

      /* compare with Threshold */
      if(sample > loc_AppRtData.Results.NoiseAtgThreshold)
      {
        /* to much noise -> set HwErr Flag */
        err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_ATG_NOISE_OUT_OF_RANGE);
      }
      else
      {
        /* everything ok -> do nothing */
      }
    }
    else
    {
      /* Added to satisfy the coding rules. */
    }
  }
}

/* **************************************************************************//**
 * @brief
 * Function related to Task State Post Measurement
 *
 * Cleans up after measurement has been finished or aborted
 * and switches back to idle state
 *
 * SM13: Driver default states
 * (for details see SafetyManual)
 * 
 * SM14: Safe burst interrupt
 * (for details see SafetyManual)
 *
 * @return      none
 * ****************************************************************************/
void loc_TaskState_POST_MEAS(void)
{
  /* if not in lab or applab mode, disable tick timer and switch to IDLE mode */
  if((meas_eMeasMode_APPLICATION == loc_AppRtData.RuntimeData.MeasurementMode) || (meas_eMeasMode_APPLICATION2 == loc_AppRtData.RuntimeData.MeasurementMode) )
  {
    /* disable the timer for noise measurement */
    SWT_IRQ_DISABLE(swtimer_IRQ_EVT_CNT_ZERO_TickPeriodTimer);
    SWT_CTRL_IRQ_CLEAR(swtimer_IRQ_EVT_CNT_ZERO_TickPeriodTimer);
    SWT_DISABLE(swtimer_eTickPeriodTimer);
    /* switch to idle mode */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_IDLE;
  }
  else if ( NO_MONITOR_DATA_SELECTED == loc_AppRtData.Parameters.data.Monitoring.halfwords[1] ) 
  {
    /* if no Monitor channels active but labmode is selected 
       switch to idle mode */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_IDLE;
  }
  else if ( meas_eMeas_STATE_POST_LAB == loc_AppRtData.CurrentState )
  {
    loc_AppRtData.CurrentState = meas_eMeas_STATE_IDLE;
  }
  
  /* see SM14 */
  BRG_CTRL_HALT();
  /* disable all timers */
  SWT_IRQ_DISABLE(swtimer_IRQ_EVT_CNT_ZERO_SyncTimer);
  SWT_CTRL_IRQ_CLEAR(swtimer_IRQ_EVT_CNT_ZERO_SyncTimer);
  SWT_DISABLE(swtimer_eSyncTimer);
  /* disable dma */
  app_DeactivateDmaForEchoMeas(); /* SMA52417-140 */
  /* switch burst pulses to zero, to prevent pulse generation on accident see SM13 */
  BRG_BRG_CFG_bit.n_pulses          = 0;
  /* reset abortion flag */
  loc_AppRtData.RuntimeData.MeasAbortFlag = FALSE;
}

/* **************************************************************************//**
 * @brief
 * Read back after write
 *
 * Compares written register values to the value we expect in that register
 *
 * @param       dataFromRegister    data from register which should be compared
 * @param       dataExpected        data which should have been saved into the register
 *
 * @return      none
 * ****************************************************************************/
void loc_readBackAfterWrite(uint16_t dataFromRegister, uint16_t dataExpected)
{
  if(dataFromRegister == dataExpected)
  {
    /* data is correct */
  }
  else
  {
    /* data is incorrect -> abort measurement and set error */
    loc_AppRtData.RuntimeData.MeasAbortFlag = true;
    err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_VERIFICATION_OF_CONF_FAILED);
  }
}

/* **************************************************************************//**
 * @brief
 * Check for Abortion
 *
 * Checks, if the measurement abortion flag has been set and
 * executes the abortion
 *
 * @return      true  if measurement has been aborted
 *              false if measurement will continue
 * ****************************************************************************/
bool_t loc_checkForAbortion(void)
{
  bool_t retval = FALSE;
  if(TRUE == loc_AppRtData.RuntimeData.MeasAbortFlag)
  {
    /* Abortion Flag has been set -> handle abortion */
    loc_AppRtData.CurrentState = meas_eMeas_STATE_POST_MEAS;
    /* check transducer driver status (only if SignalPathTests is inactive) */
    if (0u == SYSTEM_CTRL_BIST)
    {
      loc_check_TdrStat();
    }
    retval = TRUE;
  }
  else
  {
    /* Abortion Flag has not been set */
  }
  return retval;
}

/* **************************************************************************//**
 * @brief
 * Check TDR status after burst
 *
 * Checks, if the TDR had an error during burst and sets the related error flag
 * heck if drv1/drv2/drvs failure flag is set after burst
 *
 * SM22: Driver voltage monitoring
 * (for details see SafetyManual)
 *
 * @return      -
 * ****************************************************************************/
void loc_check_TdrStat(void)
{
  /* check drvs status bit */
  if ( brg_eTDRStatus_Normal != BRG_TDR_STATUS_DRVS_GET() )
  {
    err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_DRVS_FAILURE_DURING_BURST);
  }
  /* check drv1 status bit */
  if ( brg_eTDRStatus_Normal != BRG_TDR_STATUS_DRV1_GET() )
  {
    err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_DRV1_FAILURE_DURING_BURST);
  }
  /* check drv2 status bit */
  if ( brg_eTDRStatus_Normal != BRG_TDR_STATUS_DRV2_GET()  )
  {
    err_SetHwErrorFlag(ERR_NO_ERROR1, ERR_DRV2_FAILURE_DURING_BURST);
  }
}
        

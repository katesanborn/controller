//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller.h
//
// Code generated for Simulink model 'controller'.
//
// Model version                  : 1.44
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Wed May  6 10:24:19 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef controller_h_
#define controller_h_
#include "rtwtypes.h"
#include "slros_initialize.h"
#include "controller_types.h"
#include <stddef.h>

// Block signals (default storage)
struct B_controller_T {
  SL_Bus_controller_std_msgs_Float64 In1;// '<S9>/In1'
  SL_Bus_controller_std_msgs_Float64 In1_b;// '<S8>/In1'
  SL_Bus_controller_std_msgs_Float64 In1_bg;// '<S7>/In1'
};

// Block states (default storage) for system '<Root>'
struct DW_controller_T {
  ros_slroscpp_internal_block_P_T obj; // '<S2>/SinkBlock'
  ros_slroscpp_internal_block_S_T obj_m;// '<S5>/SourceBlock'
  ros_slroscpp_internal_block_S_T obj_p;// '<S4>/SourceBlock'
  ros_slroscpp_internal_block_S_T obj_e;// '<S3>/SourceBlock'
};

// Invariant block signals (default storage)
struct ConstB_controller_T {
  real_T Divide;                       // '<S6>/Divide'
};

// Real-time Model Data Structure
struct tag_RTM_controller_T {
  const char_T * volatile errorStatus;
  const char_T* getErrorStatus() const;
  void setErrorStatus(const char_T* const volatile aErrorStatus);
};

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_controller_T controller_B;

#ifdef __cplusplus

}

#endif

// Block states (default storage)
extern struct DW_controller_T controller_DW;
extern const ConstB_controller_T controller_ConstB;// constant block i/o

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void controller_initialize(void);
  extern void controller_step(void);
  extern void controller_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_controller_T *const controller_M;

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'controller'
//  '<S1>'   : 'controller/Blank Message1'
//  '<S2>'   : 'controller/Publish1'
//  '<S3>'   : 'controller/Subscribe'
//  '<S4>'   : 'controller/Subscribe1'
//  '<S5>'   : 'controller/Subscribe4'
//  '<S6>'   : 'controller/controller_subsystem'
//  '<S7>'   : 'controller/Subscribe/Enabled Subsystem'
//  '<S8>'   : 'controller/Subscribe1/Enabled Subsystem'
//  '<S9>'   : 'controller/Subscribe4/Enabled Subsystem'

#endif                                 // controller_h_

//
// File trailer for generated code.
//
// [EOF]
//

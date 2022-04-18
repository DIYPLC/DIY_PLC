#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

void PLC_Ts_ms(struct GlobalVar *p);
void PLC_Ts(struct GlobalVar *p);
void PLC_Ts_ms_max(struct GlobalVar *p);
void PLC_Pulses_1000ms(struct GlobalVar *p);
void PLC_Digital_output_init(void);
void PLC_Digital_output_cyclic(struct GlobalVar *p);
void PLC_Digital_input_cyclic(struct GlobalVar *p);
void Program_delay_500ms(void);

#ifdef __cplusplus
}
#endif

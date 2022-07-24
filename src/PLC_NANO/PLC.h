#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t Calc_Ts_ms(uint32_t Uptime_ms); //Время предидущего скана ПЛК [мс].
uint32_t Calc_Ts_ms_max(uint32_t Ts_ms); //Максимальное время скана ПЛК [мс].

#ifdef __cplusplus
}
#endif

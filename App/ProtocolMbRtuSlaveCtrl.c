
#include "ProtocolMbRtuSlaveCtrl.h"

#include "App.h"
#include "BSP.h"

uint8_t modbusBufRxTxRtu485[MODBUS_SS_BUF_CNT];

//--------------------  PROTOCOL ---------------------//
//---1000
#define MDB_TABLE_BSP_REG_NO (1000)
enum mdb_table_bsp
{
  tab_bsp_state_led_rele = MDB_TABLE_BSP_REG_NO,
  tab_bsp_control_led_rele,
  tab_bsp_spi_buf_0,
  tab_bsp_spi_buf_1,
  tab_bsp_spi_buf_2,
  tab_bsp_ADC_data,
  tab_bsp_ADC_CPU_data
};
#define MDB_BSP_BUF_COUNT (tab_bsp_ADC_CPU_data - MDB_TABLE_BSP_REG_NO + 1)
uint16_t mdb_bsp_buf[MDB_BSP_BUF_COUNT];

ModbusSS_table_t mdb_table_bsp = {
    .buf = (uint8_t *)mdb_bsp_buf,
    .quantity = MDB_BSP_BUF_COUNT,
    .regNo = MDB_TABLE_BSP_REG_NO,
    .type = ModbusSS_Holding};

//--------------------  PROTOCOL END---------------------//

//--------------------  TABLES ARRAY ---------------------//
ModbusSS_table_t *modbusTables[] = {
    &mdb_table_bsp
};
//--------------------  TABLES ARRAY END---------------------//

//--------------------  MODBUS STRUCT ---------------------//
ModbusSS_t modbusSS_rtu_rs485 = {
    .cbHoldingUpdate = protocolMbRtuSlaveCtrl_callback_H_WRITE,
    .cbHoldingRequest = NULL, // protocolMbRtuSlaveCtrl_callback_H_REQ, //modbusHoldingReq,
    .rtuTcp = MODBUS_SS_RTU,
    .bufRxTx = modbusBufRxTxRtu485,
    .slaveId = 1,
    .tables = modbusTables,
    .tablesCount = 1
};
protocolMbRtuSlaveCtrl_typedef modbusRtu_ctrlStruct; // protocol control struct
//--------------------  MODBUS STRUCT END---------------------//

//------------------------ EXTERN ------------------------
extern App_struct App;
//---------------------- EXTERN END-----------------------

//------------------------ REGULAR FCN ------------------------
void protocolMbRtuSlaveCtrl_init(uint8_t portNo)
{
  HAL_Delay(100);
  bsp_rs485_setPortToModbusRtu(portNo, modbusBufRxTxRtu485, MODBUS_SS_BUF_CNT);
}

__INLINE void protocolMbRtuSlaveCtrl_update_tables()
{
  // --- BSP -----------------------------//
  ModbusSS_SetWord(&mdb_table_bsp, tab_bsp_state_led_rele,    App.Mdb_data_AO.state_led_rele);
  ModbusSS_SetWord(&mdb_table_bsp, tab_bsp_control_led_rele,  0);
  ModbusSS_SetWord(&mdb_table_bsp, tab_bsp_spi_buf_0,         App.Mdb_data_AO.spi_buf_0[0]);
  ModbusSS_SetWord(&mdb_table_bsp, tab_bsp_spi_buf_1,         App.Mdb_data_AO.spi_buf_0[1]);
  ModbusSS_SetWord(&mdb_table_bsp, tab_bsp_spi_buf_2,         App.Mdb_data_AO.spi_buf_0[2]);
  ModbusSS_SetWord(&mdb_table_bsp, tab_bsp_ADC_data,          App.Mdb_data_AO.ADC_data);
}
//------------------------ REGULAR FCN END------------------------

//------------------------------- MODBUS CALLBACKS -------------------------------------------//
#define PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK (0xAAAA)
#define PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_FAIL (0xF00F)
__weak void protocolMbRtuSlaveCtrl_callback_H_WRITE(ModbusSS_table_t *table, uint16_t reg, uint16_t quantity)
{
  // uint16_t response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_FAIL;
  // uint16_t param = 0;
  // float analog_kMul = 0.000001;
  // float kMul = 0.001f;
  // float kMulBms = 0.1f;
  // float value = 0.0f;
  // uint8_t idx = 0;
  // int16_t sign_val = 0;
  // asm("NOP");

  // if (table == &mdb_table_program) // Диапазон PROGRAM
  // {
  //   switch (reg)
  //   {
  //   case tab_prg_cmd:
  //     modbusRtu_ctrlStruct.cmd = ModbusSS_GetWord(&mdb_table_program, reg);
  //     switch (modbusRtu_ctrlStruct.cmd)
  //     {
  //     case protocol_cmd_debug:
  //       /* code */
  //       if (Program_GoDebug())
  //       {
  //         response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //       }
  //       break;
  //     case protocol_cmd_save_param:
  //       if (Program_ParamSave())
  //       {
  //         response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //       }
  //       break;
  //     case protocol_cmd_reset:
  //       if (Program_GoReset())
  //       {
  //         response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //       }
  //       break;
  //     case protocol_cmd_pwmOuts123:
  //     case protocol_cmd_pwmOuts456:
  //       param = ModbusSS_GetWord(&mdb_table_program, tab_prg_param);
  //       if (Program_set_pwmOuts_debug(modbusRtu_ctrlStruct.cmd - protocol_cmd_pwmOuts123, param))
  //       {
  //         response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //       }
  //       break;
  //     case protocol_cmd_startStopVodorod:
  //       param = ModbusSS_GetWord(&mdb_table_program, tab_prg_param);
  //       if (Program_StartStopVodorod(param))
  //       {
  //         response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //       }
  //       break;
  //     case protocol_cmd_startStopZU:
  //       param = ModbusSS_GetWord(&mdb_table_program, tab_prg_param);
  //       if (Program_StartStopZU(param))
  //       {
  //         response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //       }
  //       break;
  //     case protocol_cmd_loadDefaultParam:
  //       if (Program_LoadDefaultParam_debug())
  //       {
  //         response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //       }
  //       break;
  //     case protocol_cmd_startStopBAT:
  //       param = ModbusSS_GetWord(&mdb_table_program, tab_prg_param);
  //       if (Program_StartStopBAT(param))
  //       {
  //         response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //       }
  //       break;
  //     case protocol_cmd_ZU_set_voltage:
  //       param = ModbusSS_GetWord(&mdb_table_program, tab_prg_param);
  //       Program_ZU_setVoltage(param);
  //       response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //       break;
  //     case protocol_cmd_ZU_set_current:
  //       param = ModbusSS_GetWord(&mdb_table_program, tab_prg_param);
  //       Program_ZU_setCurrent(param);
  //       response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //       break;
  //     default:
  //       response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_FAIL;
  //       break;
  //     }
  //     break;
  //   case tab_prg_analogVal_vodorod_i_SUI1 ... tab_prg_analogVal_zu_u_CH:
  //     idx = reg - tab_prg_analogVal_vodorod_i_SUI1;
  //     float value = ModbusSS_GetWord(&mdb_table_program, reg);
  //     if (value == 0.0f)
  //     {
  //       if (Program_analogSetZero(idx))
  //       {
  //         response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //       }
  //     }
  //     else
  //     {
  //       if (Program_analogCalibKMul(idx, value))
  //       {
  //         response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //       }
  //     }
  //     break;
  //   case tab_prg_pwm1:
  //   case tab_prg_pwm1 + 1:
  //   case tab_prg_pwm1 + 2:
  //   case tab_prg_pwm1 + 3:
  //   case tab_prg_pwm1 + 4:
  //   case tab_prg_pwm1 + 5:

  //     if (Program_set_pwm_debug(reg - tab_prg_pwm1, ModbusSS_GetWord(&mdb_table_program, reg)))
  //     {
  //       response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     }
  //     break;
  //   default:
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_FAIL;
  //     break;
  //   }
  // }
  // else if (table == &mdb_table_bsp) // Диапазон BSP
  // {
  //   switch (reg)
  //   {
  //   case tab_bsp_dout:
  //     if (Program_set_dout_debug(ModbusSS_GetWord(&mdb_table_bsp, reg)))
  //     {
  //       response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     }
  //     break;
  //   default:
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_FAIL;
  //     break;
  //   }
  // }
  // else if (table == &mdb_table_regul)
  // {
  //   value = ModbusSS_GetWord(&mdb_table_regul, reg);
  //   switch (reg)
  //   {
  //   case tab_regul_vodorod_u_kP:
  //     programStruct.setupParam.vodorod_RegU_kp = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_regul_vodorod_u_kI:
  //     programStruct.setupParam.vodorod_RegU_ki = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_regul_vodorod_u_outMax:
  //     programStruct.setupParam.vodorod_RegU_MAX = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_regul_vodorod_i_kP:
  //     programStruct.setupParam.vodorod_RegI_kp = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_regul_vodorod_i_kI:
  //     programStruct.setupParam.vodorod_RegI_ki = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_regul_vodorod_i_outMax:
  //     programStruct.setupParam.vodorod_RegI_MAX = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //     //--------------------- ZU ---------------------------------//
  //   case tab_regul_ZU_u_in:
  //     programStruct.setupParam.ZU_RegU_in = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_regul_ZU_u_kP:
  //     programStruct.setupParam.ZU_RegU_kp = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_regul_ZU_u_kI:
  //     programStruct.setupParam.ZU_RegU_ki = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_regul_ZU_u_outMax:
  //     programStruct.setupParam.ZU_RegU_MAX = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_regul_ZU_i_kP:
  //     programStruct.setupParam.ZU_RegI_kp = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_regul_ZU_i_kI:
  //     programStruct.setupParam.ZU_RegI_ki = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_regul_ZU_i_outMax:
  //     programStruct.setupParam.ZU_RegI_MAX = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //     //--------------------- ZU END---------------------------------//
  //   default:
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_FAIL;
  //     break;
  //   }
  // }
  // else if (table == &mdb_table_param)
  // {
  //   value = ModbusSS_GetWord(&mdb_table_param, reg);
  //       switch (reg)
  //   {
  //   case tab_param_analog_shift_1_11 ... tab_param_analog_shift_1_11 + PRG_ANALOG_COUNT - 1:
  //     idx = reg - tab_param_analog_shift_1_11;
  //     if(Program_analogSetShift(idx, value)){
  //       response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     }
  //     break;
  //   case tab_param_analog_kMul_1_11 ... tab_param_analog_kMul_1_11 + PRG_ANALOG_COUNT - 1:
  //     idx = reg - tab_param_analog_kMul_1_11;
  //     sign_val = value;
  //     if(Program_analogSetKMul(idx, sign_val * analog_kMul)){
  //       response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     }
  //     break;
  //   case tab_param_analog_av_order_1_11 ... tab_param_analog_av_order_1_11 + PRG_ANALOG_COUNT - 1:
  //     idx = reg - tab_param_analog_av_order_1_11;
  //     if(Program_analogSetAvOrder(idx, value)){
  //       response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     }
  //     break;
  //   case tab_param_analog_filter_N_1_11 ... tab_param_analog_filter_N_1_11 + PRG_ANALOG_COUNT - 1:
  //     idx = reg - tab_param_analog_filter_N_1_11;
  //     if(Program_analogSetFilterN(idx, value)){
  //       response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     }
  //     break;
  //   case tab_param_protect_control_B_1:
  //     programStruct.setupParam.protect_control &= 0xFFFFFFFFFFFF0000;
  //     programStruct.setupParam.protect_control |= (uint64_t)value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_protect_control_B_2:
  //     programStruct.setupParam.protect_control &= 0xFFFFFFFF0000FFFF;
  //     programStruct.setupParam.protect_control |= ((uint64_t)value << 16);
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_protect_control_B_3:
  //     programStruct.setupParam.protect_control &= 0xFFFF0000FFFFFFFF;
  //     programStruct.setupParam.protect_control |= ((uint64_t)value << 32);
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_protect_control_B_4:
  //     programStruct.setupParam.protect_control &= 0x0000FFFFFFFFFFFF;
  //     programStruct.setupParam.protect_control |= ((uint64_t)value << 48);
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_reg_u_in:
  //     programStruct.setupParam.vodorod_RegU_in = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_reg_u_kp:
  //     programStruct.setupParam.vodorod_RegU_kp = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break; 
  //   case tab_param_vodorod_reg_u_ki:
  //     programStruct.setupParam.vodorod_RegU_ki = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break; 
  //   case tab_param_vodorod_reg_u_max:
  //     programStruct.setupParam.vodorod_RegU_MAX = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break; 
  //   case tab_param_vodorod_reg_i_in_max:
  //     programStruct.setupParam.vodorod_RegI_in_MAX = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_reg_i_kp:
  //     programStruct.setupParam.vodorod_RegI_kp = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_reg_i_ki:
  //     programStruct.setupParam.vodorod_RegI_ki = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_reg_i_max:
  //     programStruct.setupParam.vodorod_RegI_MAX = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_zi:
  //     Program_Vodorod_setZI(value);
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_ZU_reg_u_in:
  //     Program_ZU_setVoltage(value);
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_ZU_reg_u_kp:
  //     programStruct.setupParam.ZU_RegU_kp = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_ZU_reg_u_ki:
  //     programStruct.setupParam.ZU_RegU_ki = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_ZU_reg_u_max:
  //     Program_ZU_setCurrent(value);
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_ZU_reg_i_kp:
  //     programStruct.setupParam.ZU_RegI_kp = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_ZU_reg_i_ki:
  //     programStruct.setupParam.ZU_RegI_ki = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_ZU_reg_i_max:
  //     programStruct.setupParam.ZU_RegI_MAX = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_ZU_check_u_CH:
  //     programStruct.setupParam.ZU_check_u_CH = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_ZU_check_u_CHO_bat_connect:
  //     programStruct.setupParam.ZU_check_u_CHO_bat_connect = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_BAT_check_min_voltage:
  //     programStruct.setupParam.BAT_check_min_voltage = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_check_uIn_min:
  //     programStruct.setupParam.vodorod_check_uIn_min = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_check_uIn_max:
  //     programStruct.setupParam.vodorod_check_uIn_max = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_check_uOut_max:
  //     programStruct.setupParam.vodorod_check_uOut_max = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_check_iIn_max:
  //     programStruct.setupParam.vodorod_check_iIn_max = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_check_iOut_max:
  //     programStruct.setupParam.vodorod_check_iOut_max = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_ZU_ptotect_MaxU_CHO:
  //     programStruct.setupParam.ZU_ptotect_MaxU_CHO = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_ZU_ptotect_MaxI_CHO:
  //     programStruct.setupParam.ZU_ptotect_MaxI_CHO = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_check_uOut_min:
  //     programStruct.setupParam.vodorod_check_uOut_min = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_i_comp_onOff:
  //     Program_Vodorod_set_i_comp_onOff(value);
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_i_charge_bat:
  //     programStruct.setupParam.vodorod_i_charge_bat = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_check_bat_cell_Umin:
  //     programStruct.setupParam.check_bat_cell_Umin = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_check_bat_cell_Umax:
  //     programStruct.setupParam.check_bat_cell_Umax = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_check_bat_cell_Tmax_charge:
  //     programStruct.setupParam.check_bat_cell_Tmax_charge = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_check_bat_cell_Tmin_charge:
  //     sign_val = value;
  //     programStruct.setupParam.check_bat_cell_Tmin_charge = sign_val;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_check_bat_cell_Tmax_disch:
  //     programStruct.setupParam.check_bat_cell_Tmax_disch = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;     
  //   case tab_param_check_bat_cell_Tmin_disch:
  //     sign_val = value;
  //     programStruct.setupParam.check_bat_cell_Tmin_disch = sign_val;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;  
  //   case tab_param_ZU_i_charge_off:
  //     programStruct.setupParam.ZU_i_charge_off = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_ZU_time_wait_charge_off:
  //     programStruct.setupParam.ZU_time_wait_charge_off = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;    
  //   case tab_param_timeout_mdb_pan:
  //     programStruct.setupParam.timeout_mdb_pan = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;    
  //   case tab_param_timeout_BNE_KM_OFF:
  //     programStruct.setupParam.timeout_BNE_KM_OFF = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_Umin_cell_on_precharge:
  //     programStruct.setupParam.vodorod_Umin_cell_on_precharge = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_Uout_off_precharge:
  //     programStruct.setupParam.vodorod_Uout_off_precharge = value * kMul;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_check_bat_logic_Tmax:
  //     programStruct.setupParam.check_bat_logic_Tmax = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;      
  //   case tab_param_check_Tmax_radiator:
  //     programStruct.setupParam.check_Tmax_radiator = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_timeout_vodorod_wait_udc:
  //     programStruct.setupParam.timeout_vodorod_wait_udc = value;
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   case tab_param_vodorod_Pin_limit:
  //     Program_Vodorod_set_Pin_limit(value);
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_OK;
  //     break;
  //   default:
  //     response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_FAIL;
  //     break;
  //   }
  // }
  // //-----------------------BMS----------------------//
  // else if (table == &mdb_table_bms)
  // {
  //   value = ModbusSS_GetWord(&mdb_table_bms, reg);
  //   switch (reg) 
  //   {
  //     case tab_param_bms_mdb_state:
  //       programStruct.BmsParam.mdb_state = (uint8_t)value;
  //       programStruct.PanParam.mdb_rx = PAN_MDB_STATE_OK;
  //       break; 
  //     case tab_param_bms_bat_cell_Umin:
  //       programStruct.BmsParam.bat_cell_Umin = value*kMul;
  //       programStruct.PanParam.mdb_rx = PAN_MDB_STATE_OK;
  //       break;
  //     case tab_param_bms_bat_cell_Umax:
  //       programStruct.BmsParam.bat_cell_Umax = value*kMul;
  //       programStruct.PanParam.mdb_rx = PAN_MDB_STATE_OK;
  //       break;
  //     case tab_param_bms_bat_cell_Tmin:
  //       sign_val = ModbusSS_GetWord(&mdb_table_bms, reg);
  //       programStruct.BmsParam.bat_cell_Tmin = sign_val*kMul;
  //       programStruct.PanParam.mdb_rx = PAN_MDB_STATE_OK;
  //       break;
  //     case tab_param_bms_bat_cell_Tmax:
  //       programStruct.BmsParam.bat_cell_Tmax = value*kMul;
  //       programStruct.PanParam.mdb_rx = PAN_MDB_STATE_OK;
  //       break;
  //     case tab_param_bms_logic_Tmax:
  //       programStruct.BmsParam.logic_Tmax = value*kMulBms;
  //       programStruct.PanParam.mdb_rx = PAN_MDB_STATE_OK;
  //       break;
  //     case tab_param_bms_rellay_state:
  //       programStruct.BmsParam.rellay_state = (uint8_t)value;
  //       programStruct.PanParam.mdb_rx = PAN_MDB_STATE_OK;
  //       break;
  //   }
  // }
  // //---------------------BMS END---------------------//
  // else // Вне диапазона
  // {
  //   response = PROTOCOL_MB_RTU_SLAVE_CTRL_CMD_FAIL;
  // }

  // ModbusSS_SetWord(&mdb_table_program, tab_prg_cmd, response);
}

__weak void protocolMbRtuSlaveCtrl_callback_H_READ(ModbusSS_table_t *table, uint16_t reg, uint16_t quantity)
{

  asm("NOP");
  //             if (table == &modbusTableHolding1)
  // {
  //   for (int r = reg; r < reg + quantity; r++)
  //   {
  //     asm("NOP");
  //     switch (r)
  //     {
  //     case MBP_AI1_X:
  //       ModbusSS_SetWord(table, r, bsp_ai_read_cache(BSP_AI1));
  //       asm("NOP");
  //       break;
  //     case MBP_AI2_Y:
  //       ModbusSS_SetWord(table, r, bsp_ai_read_cache(BSP_AI2));
  //       asm("NOP");
  //       break;
  //     case MBP_DI_STATE:
  //       ModbusSS_SetWord(table, r, bsp_di_get_cache_pack16());
  //       asm("NOP");
  //       break;
  //     default:
  //       break;
  //     }
  //   }
  // }
}
//------------------------------- MODBUS CALLBACKS END-------------------------------------------//

//------------------------------- HW CALLBACK -------------------------------------------//
void bsp_rs485_callback_rxBlockReady(uint8_t portNo)
{

  int32_t blockSizeByte = 0;
  if ((blockSizeByte = ModbusSS_ParseRxData(&modbusSS_rtu_rs485)) == 0)
  {
    // bug with reset modbus!!!
    asm("NOP");
  }
  else if (blockSizeByte != -1)
  {
    asm("NOP");
    bsp_rs485_sendBlock(portNo, modbusSS_rtu_rs485.bufRxTx, blockSizeByte);
    asm("NOP");
  }
}
//------------------------------- HW CALLBACK END-------------------------------------------//





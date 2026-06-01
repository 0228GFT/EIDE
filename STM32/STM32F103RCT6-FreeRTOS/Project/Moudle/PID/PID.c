#include <math.h>
#include <stdbool.h>
#include "Board.h"
#include "PID.h"

/**
 * @brief 位置式PID结构体初始化
 * 
 * @param PID_Structure 位置PID结构体 
 */
void PositionPID_StructInit(PositionPID_StructTypeDef * PID_Structure)
{
    PID_Structure->Target_Val = 0;  //目标速度
    PID_Structure->Actual_Val = 0;  //实际速度
    PID_Structure->Output_Val = 0;	//输出值

    PID_Structure->Err = 0;			//本次误差
    PID_Structure->Err_Prev = 0;	//上次误差
    PID_Structure->Err_Sum = 0;		//误差积累

    PID_Structure->Kp = 0;			//P,快
    PID_Structure->Ki = 0;			//I,准
    PID_Structure->Kd = 0;			//D,稳

//积分分离时使用
#if Integral_Separation

    PID_Structure->Separation_Percent = PositionPID_Circle * PositionPID_Err_Circle_Percent;	//位置环周期

#endif

//积分变速时使用
#if Integral_Variable

    PID_Structure->VariableRate = 0;	//积分变速比例

#endif

//微分先行时使用
#if Differential_Advance

    PID_Structure->Target_Prev = 0;	//上次目标值

#endif

}

/**
 * @brief 设置位置式PID模式
 * 
 * @param PID_Structure 位置式PID结构体
 * @param Mode 模式
 * @note PositionPID_Mode_Position:定位模式
 * @note PositionPID_Mode_Speed:定速模式
 */
void PositionPID_ModeSet(PositionPID_StructTypeDef * PID_Structure, bool Mode)
{
    PID_Structure->PID_Mode = Mode;
}


/**
 * @brief 位置式PID计算
 * 
 * @param PID_Structure 位置式PID结构体
 */
void Position_PID(PositionPID_StructTypeDef * PID_Structure)
{
	//本次误差变为上次误差
    PID_Structure->Err_Prev = PID_Structure->Err;

	//本次误差 = 目标速度 - 实际速度
    PID_Structure->Err = PID_Structure->Target_Val - PID_Structure->Actual_Val;

	if(PID_Structure->PID_Mode)	//定速模式
	{
		/*积分部分*/
		#if Integral_Variable //积分变速

			//变速积分,根据误差变化动态调整积分比例
			PID_Structure->VariableRate = 1.0f / (Integral_VariableRate_Percent * fabs(PID_Structure->Err) + 1);
			PID_Structure->Err_Sum += PID_Structure->VariableRate * PID_Structure->Err;

		#elif Integral_Separation //积分分离

			//积分分离,当误差绝对值大于位置环周期时,积分项清零
			if(fabs(PID_Structure->Err) < PID_Structure->Separation_Percent)
				PID_Structure->Err_Sum += PID_Structure->Err;
			else
				PID_Structure->Err_Sum = 0;

		#else //直接积分

			PID_Structure->Err_Sum += PID_Structure->Err;

		#endif

		// PID_Structure->Err_Sum += PID_Structure->Err;

		#if Integral_Limit //积分限幅

			//积分限幅,防止积分饱和
			if(PID_Structure->Err_Sum * PID_Structure->Ki > PositionPID_Output_SpeedMode_Max)
				PID_Structure->Err_Sum = PositionPID_Output_SpeedMode_Max / PID_Structure->Ki;
			else if(PID_Structure->Err_Sum * PID_Structure->Ki < PositionPID_Output_SpeedMode_Min)
				PID_Structure->Err_Sum = PositionPID_Output_SpeedMode_Min / PID_Structure->Ki;
		
		#endif

		/*微分部分*/
		#if Differential_Advance //微分先行
			
			//微分输出 = - D * (目标值 - 上次目标值)
			PID_Structure->Kd_Out = - PID_Structure->Kd * (PID_Structure->Target_Val - PID_Structure->Target_Prev);
			//上次目标值变为本次目标值
			PID_Structure->Target_Prev = PID_Structure->Target_Val;

		#elif Differential_Incomplete //微分不完全

			//微分输出 = (1 - 微分不完全比例) * (本次误差 - 上次误差) * D + 微分不完全比例 * 上次微分输出
			PID_Structure->Kd_Out = (1.0f - Differential_Incomplete_Percent) * (PID_Structure->Err - PID_Structure->Err_Prev) * PID_Structure->Kd + Differential_Incomplete_Percent * PID_Structure->Kd_Out;

		#endif

		/*输出部分*/
		#if Differential_Advance || Differential_Incomplete //微分先行或微分不完全

			PID_Structure->Output_Val = PID_Structure->Kp * PID_Structure->Err + PID_Structure->Ki * PID_Structure->Err_Sum + PID_Structure->Kd_Out;

		#else

			//输出 = P * 本次误差 + I * 误差积累 + D * (本次误差 - 上次误差)
			PID_Structure->Output_Val = PID_Structure->Kp * PID_Structure->Err + PID_Structure->Ki * PID_Structure->Err_Sum + PID_Structure->Kd * (PID_Structure->Err - PID_Structure->Err_Prev);

		#endif

		//输出值限幅
		if(PID_Structure->Output_Val > PositionPID_Output_SpeedMode_Max)
			PID_Structure->Output_Val = PositionPID_Output_SpeedMode_Max;
		else if(PID_Structure->Output_Val < PositionPID_Output_SpeedMode_Min)
			PID_Structure->Output_Val = PositionPID_Output_SpeedMode_Min;
	}
	else	//定位模式
	{
		#if(Input_DeadZone) //输入死区

			//输入死区,当误差绝对值小于输入死区阈值时,输出设为0
			if(fabs(PID_Structure->Err) < Input_DeadZone_Percent * PositionPID_Circle)
			{
				PID_Structure->Output_Val = 0;
				//PID_Structure->Err_Sum = 0;
			}
			else
			{
				/*积分部分*/
				#if Integral_Variable //积分变速

					//变速积分,根据误差变化动态调整积分比例
					PID_Structure->VariableRate = 1.0f / (Integral_VariableRate_Percent * fabs(PID_Structure->Err) + 1);
					PID_Structure->Err_Sum += PID_Structure->VariableRate * PID_Structure->Err;

				#elif Integral_Separation //积分分离

					//积分分离,当误差绝对值大于位置环周期时,积分项清零
					if(fabs(PID_Structure->Err) < PID_Structure->Separation_Percent)
						PID_Structure->Err_Sum += PID_Structure->Err;
					else
						PID_Structure->Err_Sum = 0;

				#else //直接积分

					PID_Structure->Err_Sum += PID_Structure->Err;

				#endif

				#if Integral_Limit //积分限幅

					//积分限幅,防止积分饱和
					if(PID_Structure->Err_Sum * PID_Structure->Ki > PositionPID_Output_PositionMode_Max)
						PID_Structure->Err_Sum = PositionPID_Output_PositionMode_Max / PID_Structure->Ki;
					else if(PID_Structure->Err_Sum * PID_Structure->Ki < PositionPID_Output_PositionMode_Min)
						PID_Structure->Err_Sum = PositionPID_Output_PositionMode_Min / PID_Structure->Ki;
				
				#endif

				/*微分部分*/
				#if Differential_Advance //微分先行
					
					//微分输出 = - D * (目标值 - 上次目标值)
					PID_Structure->Kd_Out = - PID_Structure->Kd * (PID_Structure->Target_Val - PID_Structure->Target_Prev);
					//上次目标值变为本次目标值
					PID_Structure->Target_Prev = PID_Structure->Target_Val;

				#elif Differential_Incomplete //微分不完全

					//微分输出 = (1 - 微分不完全比例) * (本次误差 - 上次误差) * D + 微分不完全比例 * 上次微分输出
					PID_Structure->Kd_Out = (1.0f - Differential_Incomplete_Percent) * (PID_Structure->Err - PID_Structure->Err_Prev) * PID_Structure->Kd + Differential_Incomplete_Percent * PID_Structure->Kd_Out;

				#endif

				/*输出部分*/
				#if Differential_Advance || Differential_Incomplete //微分先行或微分不完全

					PID_Structure->Output_Val = PID_Structure->Kp * PID_Structure->Err + PID_Structure->Ki * PID_Structure->Err_Sum + PID_Structure->Kd_Out;

				#else

					//输出 = P * 本次误差 + I * 误差积累 + D * (本次误差 - 上次误差)
					PID_Structure->Output_Val = PID_Structure->Kp * PID_Structure->Err + PID_Structure->Ki * PID_Structure->Err_Sum + PID_Structure->Kd * (PID_Structure->Err - PID_Structure->Err_Prev);

				#endif

				#if Output_Offset //输出偏移

					//输出偏移
					if(PID_Structure->Output_Val > Output_Offset_Up)
						PID_Structure->Output_Val += Output_Offset_Percent * PositionPID_Output_PositionMode_Max;
					else if(PID_Structure->Output_Val < Output_Offset_Down)
						PID_Structure->Output_Val -= Output_Offset_Percent * PositionPID_Output_PositionMode_Max;

				#endif		
			}

		#else

			/*积分部分*/
			#if Integral_Variable //积分变速

				//变速积分,根据误差变化动态调整积分比例
				PID_Structure->VariableRate = 1.0f / (Integral_VariableRate_Percent * fabs(PID_Structure->Err) + 1);
				PID_Structure->Err_Sum += PID_Structure->VariableRate * PID_Structure->Err;

			#elif Integral_Separation //积分分离

				//积分分离,当误差绝对值大于位置环周期时,积分项清零
				if(fabs(PID_Structure->Err) < PID_Structure->Separation_Percent)
					PID_Structure->Err_Sum += PID_Structure->Err;
				else
					PID_Structure->Err_Sum = 0;

			#else //直接积分

				PID_Structure->Err_Sum += PID_Structure->Err;

			#endif

			#if Integral_Limit //积分限幅

				//积分限幅,防止积分饱和
				if(PID_Structure->Err_Sum * PID_Structure->Ki > PositionPID_Output_PositionMode_Max)
					PID_Structure->Err_Sum = PositionPID_Output_PositionMode_Max / PID_Structure->Ki;
				else if(PID_Structure->Err_Sum * PID_Structure->Ki < PositionPID_Output_PositionMode_Min)
					PID_Structure->Err_Sum = PositionPID_Output_PositionMode_Min / PID_Structure->Ki;
			
			#endif

			/*微分部分*/
			#if Differential_Advance //微分先行
				
				//微分输出 = - D * (目标值 - 上次目标值)
				PID_Structure->Kd_Out = - PID_Structure->Kd * (PID_Structure->Target_Val - PID_Structure->Target_Prev);
				//上次目标值变为本次目标值
				PID_Structure->Target_Prev = PID_Structure->Target_Val;

			#elif Differential_Incomplete //微分不完全

				//微分输出 = (1 - 微分不完全比例) * (本次误差 - 上次误差) * D + 微分不完全比例 * 上次微分输出
				PID_Structure->Kd_Out = (1.0f - Differential_Incomplete_Percent) * (PID_Structure->Err - PID_Structure->Err_Prev) * PID_Structure->Kd + Differential_Incomplete_Percent * PID_Structure->Kd_Out;

			#endif

			/*输出部分*/
			#if Differential_Advance || Differential_Incomplete //微分先行或微分不完全

				PID_Structure->Output_Val = PID_Structure->Kp * PID_Structure->Err + PID_Structure->Ki * PID_Structure->Err_Sum + PID_Structure->Kd_Out;

			#else

				//输出 = P * 本次误差 + I * 误差积累 + D * (本次误差 - 上次误差)
				PID_Structure->Output_Val = PID_Structure->Kp * PID_Structure->Err + PID_Structure->Ki * PID_Structure->Err_Sum + PID_Structure->Kd * (PID_Structure->Err - PID_Structure->Err_Prev);

			#endif

			#if Output_Offset //输出偏移

				//输出偏移
				if(PID_Structure->Output_Val > Output_Offset_Up)
					PID_Structure->Output_Val += Output_Offset_Percent * PositionPID_Output_PositionMode_Max;
				else if(PID_Structure->Output_Val < Output_Offset_Down)
					PID_Structure->Output_Val -= Output_Offset_Percent * PositionPID_Output_PositionMode_Max;

			#endif

		#endif
	}

	//输出值限幅
    if(PID_Structure->Output_Val > PositionPID_Output_PositionMode_Max)
        PID_Structure->Output_Val = PositionPID_Output_PositionMode_Max;
    else if(PID_Structure->Output_Val < PositionPID_Output_PositionMode_Min)
        PID_Structure->Output_Val = PositionPID_Output_PositionMode_Min;
}

/**
 * @brief 增量式PID结构体初始化
 * 
 * @param PID_Structure 增量式PID结构体
 */
void IncrementalPID_StructInit(IncrementalPID_StructTypeDef * PID_Structure)
{
    PID_Structure->Target_Val = 0;  //目标速度
    PID_Structure->Actual_Val = 0;  //实际速度
    PID_Structure->Output_Val = 0;	//输出值

    PID_Structure->Err = 0;			//本次误差
    PID_Structure->Err_Prev1 = 0;	//上次误差
    PID_Structure->Err_Prev2 = 0;	//上上次误差

    PID_Structure->Kp = 0;			//P,快
    PID_Structure->Ki = 0;			//I,准
    PID_Structure->Kd = 0;			//D,稳

    PID_Structure->Output_Max = IncrementalPID_Output_Max;	//最大输出值
    PID_Structure->Output_Min = IncrementalPID_Output_Min;	//最小输出值
}

/**
 * @brief 增量式PID计算
 * 
 * @param PID_Structure 增量PID结构体
 */
void Incremental_PID(IncrementalPID_StructTypeDef * PID_Structure)
{
	//上次误差变为上上次误差
    PID_Structure->Err_Prev2 = PID_Structure->Err_Prev1;
	
	//本次误差变为上次误差
	PID_Structure->Err_Prev1 = PID_Structure->Err;

	//本次误差 = 目标速度 - 实际速度
    PID_Structure->Err = PID_Structure->Target_Val - PID_Structure->Actual_Val;
	
	//输出 += P * (本次误差 - 上次误差) + I * 本次误差 + D * (本次误差 - 2 * 上次误差 + 上上次误差)
    PID_Structure->Output_Val += PID_Structure->Kp * (PID_Structure->Err - PID_Structure->Err_Prev1) + PID_Structure->Ki * PID_Structure->Err + PID_Structure->Kd * (PID_Structure->Err - 2 * PID_Structure->Err_Prev1 + PID_Structure->Err_Prev2);

	//输出值限幅
    if(PID_Structure->Output_Val > PID_Structure->Output_Max)
        PID_Structure->Output_Val = PID_Structure->Output_Max;
    else if(PID_Structure->Output_Val < PID_Structure->Output_Min)
        PID_Structure->Output_Val = PID_Structure->Output_Min;
}

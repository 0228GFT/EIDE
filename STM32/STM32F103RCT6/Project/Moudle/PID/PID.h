/********************************************************************************/
/**
 * @note 位置式PID
 * 积分优化
 *      定速常用:积分限幅
 *      定位常用:积分分离、积分变速
 *          积分限幅、积分分离、积分变速,不同时使用
 * 微分优化
 *      定位常用:微分先行、微分不完全
 * 
 * 输出优化
 *      定位常用:输出偏移,常与输入死区一起使用
 * 
 * 输入优化
 *      定位常用:输入死区,常与输出偏移一起使用
 * 
 * @note 优化使用情况
 * 积分限幅:执行器不能消除误差时,误差积分无限制加大达到积分饱和,导致执行器持续最大输出,
 *          执行器恢复后短时间仍会输出最大输出,直至误差积分恢复正常
 * 积分分离:调控前期一般误差较大,无需积分作用,若仍继续积分,后期时可能积累过大的调控力,
 *          导致超调
 * 积分变速:积分分离升级版,若积分分离阈值设置不当,若被控对象正好在阈值之外停止,此时控制
 *          器完全没有积分作用
 * 微分先行:目标值大幅度跳变时,误差也会大幅度跳变,导致微分项突然输出一个很大的调控力,适
 *          用于系统目标值频繁大幅度切换
 * 微分不完全:传感器获取实际值经常受到噪声干扰,导致微分项输出不稳定
 * 输出偏移:启动需要一定力度的执行器;输出较小时带不动执行器
 * 输入死区:输入的目标值或实际值有微小的噪声波动或系统有一定滞后,导致执行器在误差很小时
 *          频繁调控,无法稳定下来
 */

#ifndef _PID_H_
#define _PID_H_


#define Integral_Limit          1   //积分限幅
#define Integral_Separation     0   //积分分离
#define Integral_Variable       1   //积分变速

#define Differential_Advance    0   //微分先行
#define Differential_Incomplete 1   //微分不完全

#define Output_Offset           1   //输出偏移
#define Input_DeadZone			1	//输入死区



#define PositionPID_Mode_Position	0	//定位模式
#define PositionPID_Mode_Speed		1	//定速模式

#define PositionPID_Output_SpeedMode_Max           100.0f  //最大输出值
#define PositionPID_Output_SpeedMode_Min          -100.0f  //最小输出值

#define PositionPID_Output_PositionMode_Max		   100.0f  //最大输出值
#define PositionPID_Output_PositionMode_Min		  -100.0f  //最小输出值

//积分分离时使用
#if Integral_Separation

    //位置环周期
    #define PositionPID_Circle              1320
    //位置环周期比例
    #define PositionPID_Err_Circle_Percent  0.12f

#endif

//积分变速时使用
#if Integral_Variable

	//位置环周期
    #define PositionPID_Circle              1320
    //变速积分比例系数,范围0.0-1.0,越大积分速度越慢
    #define Integral_VariableRate_Percent   0.1f

#endif

//微分不完全时使用
#if Differential_Incomplete

    //微分不完全比例系数,范围0.0-1.0
    #define Differential_Incomplete_Percent 0.8f

#endif

//输出偏移时使用
#if Output_Offset

    #define Output_Offset_Up        0.0f    //输出偏移上阈值
    #define Output_Offset_Down      0.0f    //输出偏移下阈值
    #define Output_Offset_Percent   0.1f	//输出偏移量比例

#endif

//输入死区时使用
#if Input_DeadZone

    #define Input_DeadZone_Percent	0.01f	//输入死区阈值比例

#endif

/**
 * @brief 位置式PID结构体
 * 
 */
typedef struct
{
    float Target_Val;       //目标速度
    float Actual_Val;       //当前速度
    float Output_Val;       //输出值
    float Err;              //本次误差
    float Err_Prev;         //上次误差
    float Err_Sum;          //误差积累
    float Kp;			    //P,快
    float Ki;			    //I,准
    float Kd;			    //D,稳
	bool PID_Mode;			//PID模式标志位,0:定位,1:定速

#if Integral_Separation     //积分分离时使用

    //积分分离比例
    float Separation_Percent;

#endif

#if Integral_Variable       //积分变速时使用

    //积分变速比例
    float VariableRate;

#endif

#if Differential_Advance     //微分先行时使用

    //上次目标值
    float Target_Prev;

#endif

//微分不完全或微分先行时使用
#if Differential_Incomplete || Differential_Advance

    //微分输出
    float Kd_Out;

#endif

} PositionPID_StructTypeDef;

void PositionPID_StructInit(PositionPID_StructTypeDef * PID_Structure);
void Position_PID(PositionPID_StructTypeDef * PID_Structure);
void PositionPID_ModeSet(PositionPID_StructTypeDef * PID_Structure, bool Mode);

/********************************************************************************/


/********************************************************************************/
/**
 * @brief 增量式PID
 * @note 定速
 * @note 定位
 */

#define IncrementalPID_Output_Max   100.0f
#define IncrementalPID_Output_Min  -100.0f

/**
 * @brief 增量式PID结构体
 * 
 */
typedef struct
{
    float Target_Val;   //目标速度
    float Actual_Val;   //当前速度
    float Output_Val;   //输出值
    float Err;          //本次误差
    float Err_Prev1;    //上次误差
    float Err_Prev2;    //上上次误差
    float Kp;			//P,快
    float Ki;			//I,准
    float Kd;			//D,稳
    float Output_Max;   //最大输出值
    float Output_Min;   //最小输出值
} IncrementalPID_StructTypeDef;

void IncrementalPID_StructInit(IncrementalPID_StructTypeDef * PID_Structure);
void Incremental_PID(IncrementalPID_StructTypeDef * PID_Structure);

/********************************************************************************/

#endif // !_PID_H_

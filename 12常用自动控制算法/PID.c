/*
 * 在过程控制中，按偏差的比例（P）、积分（I）和微分（D）进行控制的PID控制器
 * （亦称PID调节器）是应用最为广泛的一种自动控制器;
 * 对于过程控制的典型对象──“一阶滞后＋纯滞后”与“二阶滞后＋纯滞后”的控制对象，
 * PID控制器是一种最优控制;
 * PID调节规律是连续系统动态品质校正的一种有效方法，它的参数整定方式简便，结
 * 构改变灵活（PI、PD、…）。
 *
*/


#include <reg52.h>
#include <string.h>             
typedef struct PID { 
    double SetPoint;     // 设定目标Desired value 
    double Proportion;    // 比例常数Proportional Const 
    double Integral;      // 积分常数Integral Const 
    double Derivative;    // 微分常数Derivative Const 
    double LastError;    // Error[-1] 
    double PrevError;    // Error[-2] 
    double SumError;   // Sums of Errors 
} PID; 

//主程序：
double sensor (void) 
{ 
return 100.0;
}


void actuator(double rDelta) 
{

} 

void main(void) 
{ 
    PID sPID; 
    double rOut; 
    double rIn; 

    PIDInit ( &sPID ); 

    sPID.Proportion = 0.5；
    sPID.Derivative = 0.0; 
    sPID.SetPoint = 100.0; 

    for (;;) { 
        rIn = sensor(); 
        rOut = PIDCalc( &sPID,rIn ); 
        actuator( rOut ); 
        }
}

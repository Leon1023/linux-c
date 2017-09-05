/************************************
 * 01.PID算法
 * 系统设定值为set，每次样本值为x。
 * 比例常数KP:每次采样值与set的误差e_n＝set-x_n;所以调控信号control=KP*e_n
 * 积分常数KI:误差sum_e_n＝e_1+e_2+...+e_n;所以调控信号control=KI*sum_e_n
 * 微分常数 KD:误差de_n＝e_n-e_(n-1);所以调控信号control=KD*de_n
 * 总调控值:control=KP*e+KI*sum_e+KD*de_n
 *
************************************/
/*
float KP,KI,KD;
float set,LE,sum_e;//LE->the e of last time

void TaskSmpCrl(void *pdata)
{
	float new,e,de,crl;//crl->paramate of control function
	while(1){
		new=sample();
		e=set-new;
		de=e-LE;
		sum_e+=e;
		crl=KP*e+KI*sum_e+KD*de;
		Control(crl);
		LE=e;
		delay(T);
	}
}

*/


/************************************
 * 02.增量PID算法
 * 增量PID就是对原来控制信号control的求导！
 * KP:原来误差e的导数de_n＝e_n-e_(n-1);所以调控信号deta_control=KP*de_n
 * KI:误差累积和的导数就是误差;所以调控信号deta_control=KI*e
 * KD:误差增量的增量为dde;所以调控信号control=KD*dde=KD*(de_n-de_n-1)
 * 总调控值:deta_control=KP*de+KI*e+KD*(de_n-de_n-1)
 *
************************************/
/*
float KP,KI,KD;
float set,LDE;//LDE->the de of last time

void TaskSmpCrl(void *pdata)
{
	float new,e,de,crl;//crl->paramate of deta_control function
	while(1){
		new=sample();
		e=set-new;
		de=e-LE;
		dde=de-LDE;
		crl=KP*de+KI*e+KD*dde;
		Deta_Control(crl);
		LDE=de;
		delay(T);
	}
}
*/

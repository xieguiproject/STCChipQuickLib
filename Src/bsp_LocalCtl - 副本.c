#include "bsp_LocalCtl.h"
#include "stdio.h"

#if 0
uint16_t Low = 0;
bit   Jump_flag;
uint8_t Temp_addrl,Temp_addrh,Address_l,Address_h;
uint8_t cntint = 0,IR_Key = 0;	
bit   start_flag=0,IR_OVER;
uint16_t release_key;	
uint16_t RF_Value_Cnt;
uint32_t RF_data;
				 		


void soft_count()//接受吗
{
	if(RF_Dat==0)	
	{	
		Low++;
		if(Jump_flag)Jump_flag=0;		
	}
	else if(RF_Dat==1)	
	{
		if(!Jump_flag)
		{	
			Jump_flag=1;
			soft_decode();
			Low=0;
		}
	}
}

void soft_decode()
{
	if(start_flag==0)
	{
		//捕获同步码
		if(( Low > _start_us_min ) && ( Low < _start_us_max ))	
		{
			printf("Sync\n");
			start_flag=1;
			cntint=0;
			IR_Key=0;
			RF_data=0;
		}
		else 
		{
			RF_Value_Cnt=0;
			release_key++;
			if(release_key>500)release_key=500;
		}
	}
	else if((start_flag==1)&&(cntint<24))
	{
		if(( Low > _num0_us_min ) && ( Low < _num0_us_max ))
		{
			RF_data=RF_data<<1;
			cntint++;
		}
		else if(( Low > _num1_us_min ) && ( Low < _num1_us_max ))		
		{
			RF_data=RF_data<<1;
			RF_data|=1;
			cntint++;
		}
		else 
		{
			start_flag=0;
			cntint=0;
		}
	}

	if(cntint == 24)
	{
		release_key=0;
		RF_Value_Cnt++;
		if(RF_Value_Cnt>500)RF_Value_Cnt=500;

		cntint=0;
		start_flag=0;
		
		IR_Key = (uint8_t)(RF_data&0x0000000f);	
		printf("Key:%d\n",IR_Key);
		Temp_addrl=(RF_data>>4)&0x000000ff; 
		Temp_addrh=(RF_data>>12)&0x000000ff;
		IR_OVER=1;		
  }
}
#else

bit bt_auto = 0;

uint8_t temp_h = 0;
uint8_t temp_l = 0;
uint8_t hh_w,ll_w;         	//高,低电平宽度
bit old_rc5;             		//保存上一次查询到的电平状态
bit tb_ok;               		//接收到同步的马时置1   
uint8_t  mma1,mma2,mma3; 			//用于解码过程
uint8_t  bma1,bma2,bma3; 	  	//用于接收过程存放遥控编码，编码比较两次，这是第一次
uint8_t  xdata mmb1,mmb2,mmb3; //	用于接收过程存放遥控编码，第二次
bit  	 decode_ok;		 				//????
bit  	 decode_okA;		 				//解码成功
bit  	 decode_okB;		 				//解码成功
uint8_t  ma_x;              	//接收到第几位编码了
bit rf_ok1,rf_ok2;		 		//解码过程中的临时接收成功标志
uint16_t s,s1;
uint8_t s2;
bit rf_ok;               		//
bit study=0;

uint8_t xdata key_number[2][10][3];		//???????,??10????
uint8_t KEY_N[2]={0,0};//?????????
uint16_t YKBUFF = 0;      //???????
uint16_t T2time =0;
uint16_t xdata T2buff[4]={0,0,0,0};
uint16_t xdata T2timebuff[1];

void LocalCtlCb()
{
	uint8_t x1,y1;
		 
	 if(!bt_auto)	  //????????
		   {
		    T4L=0xE4;             //   430K:FE/B5   220K:FF/30
				T4H=0xFD;
		   }
		else
			{
				T4L=temp_l;             //   430K:FE/B5   220K:FF/30
				T4H=temp_h;	 
							
			} 	

	  TF0=0;                // ??T0????
    
      if (!RF_Dat) { ll_w++;old_rc5=0; }           // ?????? ??????1,????????
      	else                                      // ??????
       	{ hh_w++;
         if (!old_rc5)                          // ??????????,????????(?-?)????
          { 
						
						if (((hh_w>=2)&&(hh_w<=8))&&((ll_w>=50)&&(ll_w<=190)))          //????	  2/5 110/140
             {//=================================================================================================================================== 
							
							if((ll_w>=110)&&(ll_w<=140)){ma_x=0;tb_ok=1;bma1=0; bma2=0; bma3=0; bt_auto=0;}	 //
							else
								{
									
									if((ll_w>140)&&(ll_w<=160)){ ma_x=0;tb_ok=1;bma1=0; bma2=0; bma3=0; bt_auto=1;temp_h=0xfd;temp_l=0xb6; }//fe  6b				  
									else
									 {  
										if((ll_w>160)&&(ll_w<=190)){ ma_x=0;tb_ok=1;bma1=0; bma2=0; bma3=0; bt_auto=1;temp_h=0xfd;temp_l=0x27; } //fd  dc
										else
											{					  
												if((ll_w>70)&&(ll_w<=90)){ma_x=0;tb_ok=1;bma1=0; bma2=0; bma3=0; bt_auto=1;temp_h=0xfe;temp_l=0x7b; }	//ff  30
												else
													{
														if((ll_w>90)&&(ll_w<=110)){ma_x=0;tb_ok=1;bma1=0; bma2=0; bma3=0; bt_auto=1;temp_h=0xfe;temp_l=0x4b; }	//ff  00
														else
															{
															 if((ll_w>=50)&&(ll_w<=70)){ma_x=0;tb_ok=1;bma1=0; bma2=0; bma3=0; bt_auto=1;temp_h=0xfe;temp_l=0xc5; }//ff  7a
															}
						
													}
											}							  
									 }
							 }
							//===================================================================================================================================  
             }
             else if ((tb_ok)&&((ll_w>=10)&&(ll_w<=14))) 	//   10/14
									{ 	
										ma_x++;				//????????,?0
										if(ma_x>23)
											{
												 if(!rf_ok1)
													{
													mma1=bma1;mma2=bma2;mma3=bma3;//????????????????                             
													rf_ok1=1;                     // ????????????
													tb_ok=0;
													bt_auto=0;
													s=2000;								
												}
												else
													{
														mmb1=bma1;mmb2=bma2;mmb3=bma3;//????????????????                             
														rf_ok2=1;                     // ????????????
														tb_ok=0;
														bt_auto=0;																			
													}
											}
									 }  
								else if ((tb_ok)&&((ll_w>=2)&&(ll_w<=8)))  		 //   3/5
											{ switch (ma_x)
												 { 
													 case 0 : { bma1=bma1 | 0x80; break; }//?????1?
													 case 1 : { bma1=bma1 | 0x40; break; }
													 case 2 : { bma1=bma1 | 0x20; break; }
													 case 3 : { bma1=bma1 | 0x10; break; }
													 case 4 : { bma1=bma1 | 0x08; break; }
													 case 5 : { bma1=bma1 | 0x04; break; }
													 case 6 : { bma1=bma1 | 0x02; break; }
													 case 7 : { bma1=bma1 | 0x01; break; }
													 case 8 : { bma2=bma2 | 0x80; break; }
													 case 9 : { bma2=bma2 | 0x40; break; }
													 case 10: { bma2=bma2 | 0x20; break; }
													 case 11: { bma2=bma2 | 0x10; break; }
													 case 12: { bma2=bma2 | 0x08; break; }
													 case 13: { bma2=bma2 | 0x04; break; }
													 case 14: { bma2=bma2 | 0x02; break; }
													 case 15: { bma2=bma2 | 0x01; break; }
													 case 16: { bma3=bma3 | 0x80; break; }//2262?????1?
													 case 17: { bma3=bma3 | 0x40; break; }
													 case 18: { bma3=bma3 | 0x20; break; }
													 case 19: { bma3=bma3 | 0x10; break; }
													 case 20: { bma3=bma3 | 0x08; break; }//ev1527?????1?
													 case 21: { bma3=bma3 | 0x04; break; }
													 case 22: { bma3=bma3 | 0x02; break; }
													 case 23: { bma3=bma3 | 0x01;
								 
												if(!rf_ok1)
												{
												mma1=bma1;mma2=bma2;mma3=bma3;//????????????????                             
												rf_ok1=1;                     // ????????????
												tb_ok=0;
												bt_auto=0;
												s=2000;
												break;									
											}
											else
												{
													mmb1=bma1;mmb2=bma2;mmb3=bma3;//??????????????????,                             
													rf_ok2=1;                     // ????????????
													tb_ok=0;
													bt_auto=0;
													break;																			
												} 
																			 
																		}
												 } 
												ma_x++;
							
											}else {
														//????????-?????
														ma_x=0; tb_ok=0; bt_auto=0;bma1=0; bma2=0; bma3=0; hh_w=1;ll_w=0;
														}      
    	   ll_w=0;hh_w=1; 
  			 }          
         old_rc5=1;      // ????????
       }
	if(rf_ok1)		//????????2???????????
		{
			s--;
			if(!s){rf_ok1=0;} 
			if(rf_ok2) 
				{
				  if((mma1==mmb1)&&(mma2==mmb2)&&(mma3==mmb3))
				  	 {
					  rf_ok=1;
					  rf_ok1=0;
					  rf_ok2=0;					 
					 }
					 else
					   {
						  rf_ok=0;
						  rf_ok1=0;
						  rf_ok2=0;
					 
					   }
				  				
				}					
		}

    if((rf_ok)&&(!study))		 //?????????
			{  	
				EA=0;
				rf_ok=0;
				 for(y1=0;y1<2;y1++){
				 
			    for(x1=0;x1<10;x1++)
				   	{
						if((mma1==key_number[y1][x1][0])&&(mma2==key_number[y1][x1][1])&&(mma3==key_number[y1][x1][2] ))//
							{
								if(y1==0){//???????
									decode_ok=1;
									decode_okA=1;					
									s1=2000;
									break;
								}
								if(y1==1){//???????
									decode_ok=1;
									decode_okB=1;					
									s1=2000;
									break;
								}

							}
				
					} 
												
				}		

					EA=1;
			}


   if(decode_ok)   //??????,??2272 PT?
	  	{
			s1--;
			if(!s1)
				{
					decode_ok=0;					
				}				  
	  	}
}

#endif

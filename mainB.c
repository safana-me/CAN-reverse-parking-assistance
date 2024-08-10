#include <lpc21xx.h>
#include "header.h"

can2 r1, send;
u32 flag=0. flag1=0, flag2=0;

int main()
{
	VPBDIV = 1;                           //for ultrasonic
	can2_init();
	ultra_init();
	en_can2_interruptB();
	uart0_init(9600);
	while(1)
	{
		if(flag==1)
		{
			uart0_integer(flag);
			uart0_tx_string("Remote frame received\r\n");
			flag = 0;
			if(r1.id == 0x100)
			{
				uart0_tx_string("Remote 1\r\n");
				while(1)
				{
					u32 distance;
					uart0_tx_string("Distance\r\n");
					distance = get_distance();
					uart0_integer(distance);
					send.id = 0x123;
					send.rtr = 0;
					send.dlc = 4;
					send.byteA = distance & 0x0000ffff;
					can2_tx(send);
					uart0_tx_string("Data frametransmitted\r\n");
					delay_ms(10);
					if(r1.id == 0x200)
					{
						uart0_tx_string("Remote 2\r\n");
						break;
					}
				}
			}
		}
	}
}

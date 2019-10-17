#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <linux/input.h>
#include <sys/stat.h>
/* socket
 * connect
 * send/recv
 */


#define SERVER_PORT 170
#define PACK_LEN 968
#define DEV_PATH "/dev/input/event1"
static struct cmd {
	int cmd;
	int triger;
	int scan_period;
};

unsigned char ucSendBuf[32] = {0x88,0x001,0x55,0xaa,
		     0xff,0x01,0xff,0xff,
		     0x00,0x00,0x00,0x00,
		     0,0,0,0,	
		     0,0,0,0,
		     0,0,0,0,
		     0,0,0,0,
		     0,0,0,0		
		    };

int print_array(unsigned char * address ,int size)
{
	int i=0;
	for(i=0;i<size;)
	{
		printf("%02x ",address[i]);
		i++;
		if((i)%4 == 0)
			printf("\n");
	}	
	printf("\n");
	return 0;
}


int main(int argc, char **argv)
{
	int iSocketClient;
	struct sockaddr_in tSocketServerAddr;
	struct cmd my_cmd;
	
	int iRet;
	
	unsigned char ucRecvBuf[1500];
	int iSendLen=0;
	int iRecvLen=0;
	int i = 0;

	
	int keys_fd;
	struct input_event t;
	int req_readlen = 0;
	int frame_num=0;
	int add_len = 0;
	int frame_num_bef =0;
	int flag = 0;
	unsigned int data_msg = 0;
	unsigned int data_frame_num = 0;
	unsigned int data_frame_address =0;
	
	unsigned char first_read_zero = 0;
	int j = 0;
	int k =0;
	short peak_data;

	my_cmd.cmd = 0x55aa8801;
	my_cmd.triger = 0xffffff01;
	my_cmd.scan_period = 100;
	//noblock 
	keys_fd=open(DEV_PATH,O_NONBLOCK );//,O_RDONLY

	if(keys_fd <= 0)

	{

	printf("open /dev/input/event1 device error!\n");

	return -1;

	}

	if (argc != 2)
	{
		printf("Usage:\n");
		printf("%s <server_ip>\n", argv[0]);
		return -1;
	}

	iSocketClient = socket(AF_INET, SOCK_STREAM, 0);

	tSocketServerAddr.sin_family      = AF_INET;
	tSocketServerAddr.sin_port        = htons(SERVER_PORT);  /* host to net, short */
 	//tSocketServerAddr.sin_addr.s_addr = INADDR_ANY;
 	if (0 == inet_aton(argv[1], &tSocketServerAddr.sin_addr))
 	{
		printf("invalid server_ip\n");
		return -1;
	}
	memset(tSocketServerAddr.sin_zero, 0, 8);


	iRet = connect(iSocketClient, (const struct sockaddr *)&tSocketServerAddr, sizeof(struct sockaddr));	
	if (-1 == iRet)
	{
		printf("connect error!\n");
		return -1;
	}
	printf("connected !\n");

	

	while (1)
	{
		
		
		if(read(keys_fd, &t, sizeof(t)) == sizeof(t))

		{
			if(t.type==EV_KEY && t.value==1 && t.code == KEY_ENTER)//press enter key to  send
			{	
				//send_data_modify();
				iSendLen = send(iSocketClient, ucSendBuf, 32, 0);
				printf("iSendLen = %d \n",iSendLen);
				if (iSendLen <= 0)
				{
					close(iSocketClient);
					printf("send error !disconnect! \n");
					return -1;
				}
				printf("compeleted send data: \n");
				print_array(ucSendBuf ,32);
				flag = 1;
				
				//printf("KEY_ENTER %s\n",(t.value) ? "Pressed" : "Released");
			}		

		}
		if(flag == 1)
		{
    
			/* 接收客户端发来的数据并显示出来 */
			if(add_len == PACK_LEN) add_len =  0;
			
			req_readlen = PACK_LEN-add_len;
			//printf("req_readlen = %d \n",req_readlen);
			iRecvLen = recv(iSocketClient, &ucRecvBuf[PACK_LEN-req_readlen], req_readlen, 0);
			add_len = add_len + iRecvLen;

			frame_num_bef = frame_num;
			frame_num = ucRecvBuf[3]*256*256*256 + ucRecvBuf[2]*256*256 + ucRecvBuf[1]*256 +ucRecvBuf[0];

			//printf("frame_num is %d\n", frame_num);
			for(j = 0; j<40 ;j++)
			{
				data_msg = ucRecvBuf[11+24*j]*256*256*256 + ucRecvBuf[10+24*j]*256*256 + ucRecvBuf[9+24*j]*256 +ucRecvBuf[8+j*24];
				data_frame_num = data_msg>>20;
				data_frame_address = data_msg & 0x000fffff;
				printf("frame : %3d ", data_frame_num);
				printf("address : %6d\n", data_frame_address);
				for(k=0; k<10 ; k++)
				{
					peak_data = ucRecvBuf[13+24*j+2*k];
					peak_data = (peak_data<<8) | ucRecvBuf[12+24*j+2*k];
					printf("%4d ", peak_data);
				}
				printf("\n");
			}

			if((frame_num-frame_num_bef) != 1 && frame_num_bef!= 124999)
				printf("error!frame_num is %d\n", frame_num);

			//printf("add2 \n");
			if (iRecvLen <= 0)
			{
				if(first_read_zero == 0)
				{
					sleep(1);
				}
				else
				{
					close(iSocketClient);
					printf("recieve error ! disconnect! \n");
					return -1;
				}
				first_read_zero = 1;
			}
			else
			{
				
				if(i == 125000)
				{
					printf("iRecvLen is : %d\n", iRecvLen);
					i=0;
				}
				i++;
				first_read_zero = 0;

			}
		}
		
	}
	
	return 0;
}




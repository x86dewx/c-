#include"framebuffer.h"
#include"process.h"
#include"picture.h"
#include<head.h>
#include "log.h"



void *window(void *p)
{
    write_log(info,"终端显示开启");
	UTF8_INFO utf8_info;
    bzero(&utf8_info, sizeof(UTF8_INFO));
    strcpy(utf8_info.path, ZIKUK_FILE_BIG);
    utf8_info.width = 32;
    utf8_info.height = 32;
    init_utf8(&utf8_info);  //初始化utf8库


    int fd = init_fb("/dev/fb0");
    if(fd < 0)
    {
        write_log(error,"fb0开启失败");
        return NULL;
    }
     drow_oblique(100,0,300,1,red);
     int temputer[4]={0};
     int oxy[4]={0};
     int PH[4]={0};
     int depth[4]={0};

    while(1)
    {
        Mdatatype q={0};
        int ret = recv_mail("终端显示",pr,&q);
        if(ret != -1)
        {
            if(!strcmp(q.sendname,"获取温度"))
            {
                temputer[3] =temputer[2];
                temputer[2] =temputer[1];
                temputer[1] =temputer[0];
                temputer[0] =(int)q.temputer;
            }
            else if(!strcmp(q.sendname,"获取氧气浓度"))
            {
                oxy[3]=oxy[2];
                oxy[2]=oxy[1];
                oxy[1]=oxy[0];
                oxy[0]=(int)q.oxy;

            }
            else if(!strcmp(q.sendname,"获取PH值"))
            {
                PH[3]=PH[2];
                PH[2]=PH[1];
                PH[1]=PH[0];
                PH[0]=(int)q.PH;

            }
            if(!strcmp(q.sendname,"获取深度"))
            {
                depth[3]=depth[2];
                depth[2]=depth[1];
                depth[1]=depth[0];
                depth[0]=q.depth;

            }
        }
        drow_picture(0,0,"./780.bmp",800,600);
        display_show_utf8_str(&utf8_info,224,20,"环 境 监 测 系 统",0x00FF00FF,black);
        drow_squre(20,67,220,178,0x00FF0000);
        drow_squre(21,68,218,176,0x00FF0000);
        
        char temputer_win[64]={0};
        sprintf(temputer_win,"温度:%d",temputer[0]);
        char oxy_win[64]={0};
        sprintf(oxy_win,"氧气浓度:%d",oxy[0]);
        char PH_win[64]={0};
        sprintf(PH_win,"PH值:%d",PH[0]);
        char depth_win[64]={0};
        sprintf(depth_win,"深度:%d",depth[0]);
        display_show_utf8_str(&utf8_info,26,79,temputer_win,0x0000FFFF,black);
        display_show_utf8_str(&utf8_info,26,121,oxy_win,0x00FF00FF,black);
        display_show_utf8_str(&utf8_info,26,163,PH_win,0x0000FFFF,black);
        display_show_utf8_str(&utf8_info,26,205,depth_win,0x0000FF00FF,black);
        drow_horizontal_line(230,427,570,black);
        drow_vertical_line(520,235,565,black);

        // 坐标轴
        drow_horizontal_line(245,407,270,black);
        drow_vertical_line(250,245,168,black);
        drow_horizontal_line(525,407,270,black);
        drow_vertical_line(530,245,168,black);
        drow_horizontal_line(245,595,270,black);
        drow_vertical_line(250,438,168,black);
        drow_horizontal_line(525,595,270,black);
        drow_vertical_line(530,438,168,black);
        draw_zhe_line(temputer,250,407,15,67,3,4);
        draw_zhe_line(oxy,530,407,10,67,32,4);
        draw_zhe_line(PH,250,595,4,67,27,4);
        draw_zhe_line(depth,530,595,2,67,20,4);
        usleep(300000);
        
    }
    return NULL;
}

void draw_zhe_line(int a[],int x,int y,int start,int x_offset,int y_offset,int len)
{

    if(a[1]!=0&&a[0]!=0)
    {
        draw_x_line(x+x_offset*2,y-(a[1]-start)*y_offset,x+x_offset*3,y-(a[0]-start)*y_offset,0x009400D3);
    }
    if(a[2]!=0&&a[1]!=0)
    {
        draw_x_line(x+x_offset,y-(a[2]-start)*y_offset,x+x_offset*2,y-(a[1]-start)*y_offset,0x009400D3);
    }
    if(a[3]!=0&&a[2]!=0)
    {
        draw_x_line(x,y-(a[3]-start)*y_offset,x+x_offset,y-(a[2]-start)*y_offset,0x009400D3);
    }
}




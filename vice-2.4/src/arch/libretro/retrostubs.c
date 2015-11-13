#include "libretro.h"
#include "joystick.h"
#include "keyboard.h"
#include "machine.h"
#include "libretro-core.h"
#include "vkbd_def.h"

extern retro_input_state_t input_state_cb;

extern int vkx,vky;
extern int CTRLON;
extern int RSTOPON;
extern int NPAGE;
extern int BKGCOLOR;
extern int KCOL;
extern int SHIFTON;
extern int SHOWKEY;
extern int CROP_WIDTH;
extern int CROP_HEIGHT;

int RSTOPON=-1;
int CTRLON=-1;
int vkx=0,vky=0;
unsigned int cur_port = 2;
bool num_locked = false;

#define MATRIX(a,b) (((a) << 3) | (b))

int check_crtfile(const char * file)
{
	if(File_DoesFileExtensionMatch(file,"CRT"))
		return 1;

	return 0;
}

void quick_load()
{
	DlgFloppy_Main();
	pauseg=0;
}

void quick_option()
{
	Dialog_OptionDlg();
	pauseg=0;
}

#if 0
static void sdl_vkbd_key_press(int value, int shift)
{
    int mr, mc, neg;
    BYTE b, sb;

    b = vkbd->keytable[vkbd_x + vkbd_y*vkbd_w];

    if ((b == VKBD_COMMAND_CLOSE) && (value)) {
        sdl_vkbd_close();
        return;
    }

    if (b == VKBD_COMMAND_MOVE) {
        if (value && shift) {
            sdl_vkbd_close();
        } else {
            vkbd_move = value;
        }
        return;
    }

    neg = b & 0x08;

    if (shift && !neg) {
        sb = vkbd->shift;
        mc = (int)(sb & 0xf);
        mr = (int)((sb >> 4) & 0xf);
        keyboard_set_keyarr(mr, mc, value);
    }

    mc = (int)(b & 0x7);
    mr = (int)((b >> 4) & 0xf);

    if (neg) {
        mr = -mr;
    }

    keyboard_set_keyarr_any(mr, mc, value);
}
#endif

void Screen_SetFullUpdate(int scr)
{
   if(scr==0 ||scr>1)memset(Retro_Screen, 0, sizeof(Retro_Screen));
  //if(scr>0)if(Screen)memset(Screen->pixels,0,Screen->h*Screen->pitch);
}

void validkey(int c64_key,int key_up,unsigned char *key_matrix, unsigned char *rev_matrix, unsigned char *joystick){
//FIXME
	int row=c64_key>>3;
	int col=c64_key&0x7;
	keyboard_set_keyarr_any(row,col,key_up);
}

void pre_validkey(int c64_key,int key_up,unsigned char *key_matrix, unsigned char *rev_matrix, unsigned char *joystick){
//FIXME TAKEN FROM FRODO
	// Handle joystick emulation
	if (c64_key & 0x40 && SHOWKEY!=1) {

		BYTE j = joystick_value[cur_port];
		c64_key &= 0x1f;
		if (key_up)
			j |= c64_key;
		else
			j &= ~c64_key;

    	joystick_value[cur_port] = j;

		return;
	}

	validkey(c64_key,key_up,NULL,NULL,NULL);
}


static void translate_key(int key, bool key_up, uint8 *key_matrix, uint8 *rev_matrix, uint8 *joystick)
{
	int c64_key = -1;
	switch (key) {
		case RETROK_a: c64_key = MATRIX(1,2); break;
		case RETROK_b: c64_key = MATRIX(3,4); break;
		case RETROK_c: c64_key = MATRIX(2,4); break;
		case RETROK_d: c64_key = MATRIX(2,2); break;
		case RETROK_e: c64_key = MATRIX(1,6); break;
		case RETROK_f: c64_key = MATRIX(2,5); break;
		case RETROK_g: c64_key = MATRIX(3,2); break;
		case RETROK_h: c64_key = MATRIX(3,5); break;
		case RETROK_i: c64_key = MATRIX(4,1); break;
		case RETROK_j: c64_key = MATRIX(4,2); break;
		case RETROK_k: c64_key = MATRIX(4,5); break;
		case RETROK_l: c64_key = MATRIX(5,2); break;
		case RETROK_m: c64_key = MATRIX(4,4); break;
		case RETROK_n: c64_key = MATRIX(4,7); break;
		case RETROK_o: c64_key = MATRIX(4,6); break;
		case RETROK_p: c64_key = MATRIX(5,1); break;
		case RETROK_q: c64_key = MATRIX(7,6); break;
		case RETROK_r: c64_key = MATRIX(2,1); break;
		case RETROK_s: c64_key = MATRIX(1,5); break;
		case RETROK_t: c64_key = MATRIX(2,6); break;
		case RETROK_u: c64_key = MATRIX(3,6); break;
		case RETROK_v: c64_key = MATRIX(3,7); break;
		case RETROK_w: c64_key = MATRIX(1,1); break;
		case RETROK_x: c64_key = MATRIX(2,7); break;
		case RETROK_y: c64_key = MATRIX(3,1); break;
		case RETROK_z: c64_key = MATRIX(1,4); break;

		case RETROK_0: c64_key = MATRIX(4,3); break;
		case RETROK_1: c64_key = MATRIX(7,0); break;
		case RETROK_2: c64_key = MATRIX(7,3); break;
		case RETROK_3: c64_key = MATRIX(1,0); break;
		case RETROK_4: c64_key = MATRIX(1,3); break;
		case RETROK_5: c64_key = MATRIX(2,0); break;
		case RETROK_6: c64_key = MATRIX(2,3); break;
		case RETROK_7: c64_key = MATRIX(3,0); break;
		case RETROK_8: c64_key = MATRIX(3,3); break;
		case RETROK_9: c64_key = MATRIX(4,0); break;

		case RETROK_SPACE: c64_key = MATRIX(7,4); break;
		case RETROK_BACKQUOTE: c64_key = MATRIX(7,1); break;
		case RETROK_BACKSLASH: c64_key = MATRIX(6,6); break;
		case RETROK_COMMA: c64_key = MATRIX(5,7); break;
		case RETROK_PERIOD: c64_key = MATRIX(5,4); break;
		case RETROK_MINUS: c64_key = MATRIX(5,0); break;
		case RETROK_EQUALS: c64_key = MATRIX(5,3); break;
		case RETROK_LEFTBRACKET: c64_key = MATRIX(5,6); break;
		case RETROK_RIGHTBRACKET: c64_key = MATRIX(6,1); break;
		case RETROK_SEMICOLON: c64_key = MATRIX(5,5); break;
		case RETROK_QUOTE: c64_key = MATRIX(6,2); break;
		case RETROK_SLASH: c64_key = MATRIX(6,7); break;

		case RETROK_ESCAPE: c64_key = MATRIX(7,7); break;
		case RETROK_RETURN: c64_key = MATRIX(0,1); break;              
		case RETROK_BACKSPACE: case RETROK_DELETE: c64_key = MATRIX(0,0); break;
		case RETROK_INSERT: c64_key = MATRIX(6,3); break;
		case RETROK_HOME: c64_key = MATRIX(6,3); break;
		case RETROK_END: c64_key = MATRIX(6,0); break;
		case RETROK_PAGEUP: c64_key = MATRIX(6,0); break;
		case RETROK_PAGEDOWN: c64_key = MATRIX(6,5); break;

		case RETROK_LCTRL: case RETROK_TAB: c64_key = MATRIX(7,2); break;
		case RETROK_RCTRL: c64_key = MATRIX(7,5); break;
		case RETROK_LSHIFT: c64_key = MATRIX(1,7); break;
		case RETROK_RSHIFT: c64_key = MATRIX(6,4); break;
		case RETROK_LALT: case RETROK_LMETA: c64_key = MATRIX(7,5); break;
		case RETROK_RALT: case RETROK_RMETA: c64_key = MATRIX(7,5); break;

		case RETROK_UP: c64_key = MATRIX(0,7)| 0x80; break;
		case RETROK_DOWN: c64_key = MATRIX(0,7); break;
		case RETROK_LEFT: c64_key = MATRIX(0,2) | 0x80; break;
		case RETROK_RIGHT: c64_key = MATRIX(0,2); break;

		case RETROK_F1: c64_key = MATRIX(0,4); break;
		case RETROK_F2: c64_key = MATRIX(0,4) | 0x80; break;
		case RETROK_F3: c64_key = MATRIX(0,5); break;
		case RETROK_F4: c64_key = MATRIX(0,5) | 0x80; break;
		case RETROK_F5: c64_key = MATRIX(0,6); break;
		case RETROK_F6: c64_key = MATRIX(0,6) | 0x80; break;
		case RETROK_F7: c64_key = MATRIX(0,3); break;
		case RETROK_F8: c64_key = MATRIX(0,3) | 0x80; break;

		case RETROK_KP0: case RETROK_KP5: c64_key = 0x10 | 0x40; break;
		case RETROK_KP1: c64_key = 0x06 | 0x40; break;
		case RETROK_KP2: c64_key = 0x02 | 0x40; break;
		case RETROK_KP3: c64_key = 0x0a | 0x40; break;
		case RETROK_KP4: c64_key = 0x04 | 0x40; break;
		case RETROK_KP6: c64_key = 0x08 | 0x40; break;
		case RETROK_KP7: c64_key = 0x05 | 0x40; break;
		case RETROK_KP8: c64_key = 0x01 | 0x40; break;
		case RETROK_KP9: c64_key = 0x09 | 0x40; break;

		case RETROK_KP_DIVIDE: c64_key = MATRIX(6,7); break;
		case RETROK_KP_ENTER: c64_key = MATRIX(0,1); break;
	}

	if (c64_key < 0)
		return;

	// Handle joystick emulation
	if (c64_key & 0x40) {

		BYTE j = joystick_value[cur_port];
		c64_key &= 0x1f;
		if (key_up)
			j |= c64_key;
		else
			j &= ~c64_key;

    	joystick_value[cur_port] = j;

		return;
	}

	validkey(c64_key,key_up==true?1:0,NULL,NULL,NULL);
/*
	// Handle other keys
	bool shifted = c64_key & 0x80;
	int c64_byte = (c64_key >> 3) & 7;
	int c64_bit = c64_key & 7;
	if (key_up) {
		if (shifted) {
			key_matrix[6] |= 0x10;
			rev_matrix[4] |= 0x40;
		}
		key_matrix[c64_byte] |= (1 << c64_bit);
		rev_matrix[c64_bit] |= (1 << c64_byte);
	} else {
		if (shifted) {
			key_matrix[6] &= 0xef;
			rev_matrix[4] &= 0xbf;
		}
		key_matrix[c64_byte] &= ~(1 << c64_bit);
		rev_matrix[c64_bit] &= ~(1 << c64_byte);
	}
*/
}


void Keymap_KeyUp(int symkey,uint8 *key_matrix, uint8 *rev_matrix, uint8 *joystick)
{
	if (symkey == RETROK_NUMLOCK)
		num_locked = false;
	else
			translate_key(symkey, false, key_matrix, rev_matrix, joystick);			
}
void Keymap_KeyDown(int symkey,uint8 *key_matrix, uint8 *rev_matrix, uint8 *joystick)
{

	switch (symkey){

		case RETROK_F9:	// F9: Quick Drive file select
			pauseg=2;
			break;
		case RETROK_F10:	// F10: 
			pauseg=3;
			break;

/*
//FIXME detect retroarch hotkey
		case RETROK_F11:	// F11:
			break;
*/
		case RETROK_F12:	// F12: Reset
			machine_trigger_reset(MACHINE_RESET_MODE_SOFT);
			break;

		case RETROK_NUMLOCK:
			num_locked = true;
			break;

		case RETROK_KP_PLUS:	// '+' on keypad: FLip List NEXT
			//flilist next
			fliplist_attach_head(8, 1);
			break;
		case RETROK_KP_MINUS:	// '-' on keypad: FLip List PREV
			//flilist prev
			fliplist_attach_head(8, 0);
			break;
		case RETROK_KP_MULTIPLY:	// '*' on keypad: toggle current joy port
		    cur_port++;
			if(cur_port>2)cur_port=1;
			break;
		case RETROK_KP_DIVIDE:	// '/' on keypad: Toggle GUI 
			pauseg=1;
			break;

		default:
			translate_key(symkey, true, key_matrix, rev_matrix, joystick);
			break;
	}
}

void retro_poll_event(void)
{
	Retro_PollEvent(NULL,NULL,NULL);

    BYTE j = joystick_value[cur_port];

    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP)) {
        j |= 0x01;
    } else {
        j &= ~0x01;
    }
    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN)) {
        j |= 0x02;
    } else {
        j &= ~0x02;
    }
    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT)) {
        j |= 0x04;
    } else {
        j &=~ 0x04;
    }
    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT)) {
        j |= 0x08;
    } else {
        j &= ~0x08;
    }
    if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A)) {
        j |= 0x10;
    } else {
        j &= ~0x10;
    }
    joystick_value[cur_port] = j;

}


void virtual_kdb(char *buffer,int vx,int vy)
{

   int x, y, page;
   unsigned coul;

#if defined PITCH && PITCH == 4
unsigned *pix=(unsigned*)buffer;
#else
unsigned short *pix=(unsigned short *)buffer;
#endif

   page = (NPAGE == -1) ? 0 : 50;
   coul = RGB565(28, 28, 31);
   BKGCOLOR = (KCOL>0?0xFF808080:0);


   for(x=0;x<NPLGN;x++)
   {
      for(y=0;y<NLIGN;y++)
      {
         DrawBoxBmp((char*)pix,XBASE3+x*XSIDE,YBASE3+y*YSIDE, XSIDE,YSIDE, RGB565(7, 2, 1));
         Draw_text((char*)pix,XBASE0-2+x*XSIDE ,YBASE0+YSIDE*y,coul, BKGCOLOR ,1, 1,20,
               SHIFTON==-1?MVk[(y*NPLGN)+x+page].norml:MVk[(y*NPLGN)+x+page].shift);	
      }
   }

   DrawBoxBmp((char*)pix,XBASE3+vx*XSIDE,YBASE3+vy*YSIDE, XSIDE,YSIDE, RGB565(31, 2, 1));
   Draw_text((char*)pix,XBASE0-2+vx*XSIDE ,YBASE0+YSIDE*vy,RGB565(2,31,1), BKGCOLOR ,1, 1,20,
         SHIFTON==-1?MVk[(vy*NPLGN)+vx+page].norml:MVk[(vy*NPLGN)+vx+page].shift);	

}

int check_vkey2(int x,int y)
{
   int page;
   //check which key is press
   page= (NPAGE==-1) ? 0 : 50;
   return MVk[y*NPLGN+x+page].val;
}

void retro_virtualkb(void)
{
   // VKBD
   int i;
   //   RETRO        B    Y    SLT  STA  UP   DWN  LEFT RGT  A    X    L    R    L2   R2   L3   R3
   //   INDEX        0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15
   static int oldi=-1;

   if(oldi!=-1)
   {
      pre_validkey(oldi,0,NULL,NULL,NULL);
      oldi=-1;
   }

   if(SHOWKEY==1)
   {
      static int vkflag[5]={0,0,0,0,0};		

      if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP) && vkflag[0]==0 )
         vkflag[0]=1;
      else if (vkflag[0]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP) )
      {
         vkflag[0]=0;
         vky -= 1; 
      }

      if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN) && vkflag[1]==0 )
         vkflag[1]=1;
      else if (vkflag[1]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN) )
      {
         vkflag[1]=0;
         vky += 1; 
      }

      if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT) && vkflag[2]==0 )
         vkflag[2]=1;
      else if (vkflag[2]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT) )
      {
         vkflag[2]=0;
         vkx -= 1;
      }

      if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT) && vkflag[3]==0 )
         vkflag[3]=1;
      else if (vkflag[3]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT) )
      {
         vkflag[3]=0;
         vkx += 1;
      }

      if(vkx<0)vkx=9;
      if(vkx>9)vkx=0;
      if(vky<0)vky=4;
      if(vky>4)vky=0;

      virtual_kdb(( char *)Retro_Screen,vkx,vky);
 
      i=8;
      if(input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i)  && vkflag[4]==0) 	
         vkflag[4]=1;
      else if( !input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i)  && vkflag[4]==1)
      {
         vkflag[4]=0;
         i=check_vkey2(vkx,vky);

         if(i==-1){
            oldi=-1;
		 }
         if(i==-2)
         {
            NPAGE=-NPAGE;oldi=-1;
            //Clear interface zone					
            //Screen_SetFullUpdate();

         }
         else if(i==-3)
         {
            //KDB bgcolor
            //Screen_SetFullUpdate();
            KCOL=-KCOL;
            oldi=-1;
         }
         else if(i==-4)
         {
            //VKbd show/hide 			
            oldi=-1;
            Screen_SetFullUpdate(0);
            SHOWKEY=-SHOWKEY;
         }
         else if(i==-5)
         {
			//flilist next
			fliplist_attach_head(8, 1);
            oldi=-1;
         }
         else
         {
            if(i==-10) //SHIFT
            {
 			   pre_validkey(MATRIX(6,4),(SHIFTON == 1)?0:1,NULL,NULL,NULL);
               SHIFTON=-SHIFTON;
               //Screen_SetFullUpdate();

               oldi=-1;
            }
            else if(i==-11) //CTRL
            {               
 			   pre_validkey(MATRIX(7,2),(CTRLON == 1)?0:1,NULL,NULL,NULL);
               CTRLON=-CTRLON;
               //Screen_SetFullUpdate();

               oldi=-1;
            }
			else if(i==-12) //RSTOP
            {               
 			   pre_validkey(MATRIX(7,7),(RSTOPON == 1)?0:1,NULL,NULL,NULL);
               RSTOPON=-RSTOPON;
               //Screen_SetFullUpdate();

               oldi=-1;
            }
			else if(i==-13) //GUI
            {     
			    pauseg=1;
				SHOWKEY=-SHOWKEY;
				Screen_SetFullUpdate(0);
               oldi=-1;
            }
			else if(i==-14) //JOY PORT TOGGLE
            {    
 				//cur joy toggle
				cur_port++;if(cur_port>2)cur_port=1;
               SHOWKEY=-SHOWKEY;
               oldi=-1;
            }
            else
            {
               oldi=i;
		       pre_validkey(oldi,1,NULL,NULL,NULL);               
            }

         }
      }

	}


}



/*
 * ui.c - PSP stub/mostly empty functions.
 *
 * Written by
 *  Akop Karapetyan <dev@psp.akop.org>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"
#include "ui.h"
#include "cmdline.h"
#include "resources.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

static const cmdline_option_t cmdline_options[] = {
    { NULL },
};

static const resource_int_t resources_int[] = {
    { NULL }
};

int drive8_status, drive8_half_track;
int drive9_status, drive9_half_track;
/*
//TEST
void ui_display_drive_led(int drive_number, unsigned int led_pwm1, unsigned int led_pwm2)
{

    int status = 0;

    if (led_pwm1 > 100) {
        status |= 1;
    }
    if (led_pwm2 > 100) {
        status |= 2;
    }

    if (drive_number == 0) {
        drive8_status = status;
    }
    if (drive_number == 1) {
        drive9_status = status;
    }
}
*/
/*
//TEST
void ui_display_drive_track(unsigned int drive_number, unsigned int drive_base, unsigned int half_track_number)
{
    if (drive_number == 0) {
        drive8_half_track = half_track_number;
    }
    if (drive_number == 1) {
        drive9_half_track = half_track_number;
    }
}
*/
void ui_check_mouse_cursor(void)
{
    /* needed */
}
/*
//TEST
void ui_display_speed(float speed, float frame_rate, int warp_enabled)
{

}
*/
void ui_error(const char *format, ...)
{

   	char text[512];	   	
   	va_list	ap;	

   	if (format == NULL)return;		
		
   	va_start(ap,format );		
      		vsprintf(text, format, ap);	
   	va_end(ap);	
    fprintf(stderr, "ui_error: %s\n", text);
}

/* display current image */
/*
//TEST
void ui_display_drive_current_image(unsigned int drivenum, const char *image)
{
    // just a dummy so far 
}
*/
/*
//TEST
void ui_display_volume(int vol)
{
}
*/
/* Display a mesage without interrupting emulation */
/*
//TEST
void ui_display_statustext(const char *text, int fade_out)
{
}
*/
/*
//TEST
void ui_display_paused(int flag)
{
}
*/

/*
void ui_display_drive_current_image(unsigned int drive_number,
                                           const char *image)
{
}
*/
/*
//TEST
void ui_display_tape_control_status(int control)
{
}
*/
/*
//TEST
void ui_display_tape_counter(int counter)
{
}
*/
/*
//TEST
void ui_display_tape_current_image(const char *image)
{
}
*/
/*
//TEST
void ui_display_playback(int playback_status, char *version)
{
}
*/
/*
//TEST
void ui_display_recording(int recording_status)
{
}
*/
/*
//TEST
void ui_enable_drive_status(ui_drive_enable_t state,
                                   int *drive_led_color)
{
}
*/
/* tape-related ui, dummies so far */
/*
//TEST
void ui_set_tape_status(int tape_status)
{
}
*/

/* Update all the menus according to the current settings.  */

void ui_update_menus(void)
{
}

int ui_extend_image_dialog()
{
  return 0;
}

void ui_dispatch_events()
{
}
/*
//TEST
void ui_resources_shutdown()
{
}
*/
int video_init_cmdline_options(void)
{
    return cmdline_register_options(cmdline_options);
}

int ui_cmdline_options_init(void)
{
  return cmdline_register_options(cmdline_options);
}

int ui_init_finish()
{
  return 0;
}

int ui_init_finalize()
{
  retro_ui_init_finalize();
  return 0;
}

char* ui_get_file(const char *format,...)
{
    return NULL;
}
/*
//TEST
void ui_display_joyport(BYTE *joyport)
{
  // needed 
}
*/
/*
//TEST
void ui_display_event_time(unsigned int current, unsigned int total)
{
  // needed 
}
*/
/*
//TEST
int ui_resources_init(void)
{
  return resources_register_int(resources_int);
}
*/
void fullscreen_capability()
{
}
char *archdep_get_runtime_os(void)
{
    return "*nix";
}

char *archdep_get_runtime_cpu(void)
{
    return "Unknown CPU";
}

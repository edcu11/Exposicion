#include <iostream>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT ev;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_TIMEOUT timeout;
ALLEGRO_JOYSTICK *joystick = NULL;



ALLEGRO_BITMAP  *per   = NULL;
ALLEGRO_BITMAP  *fondo   = NULL;
int width =968, height = 700, FPS = 30, seconds=1, timer2=0;
bool salir=true;
int alinit()
{
    if(!al_init())
    {
        cout<<"failed to initialize allegro!\n"<<endl;
        return -1;
    }

    if(!al_init_image_addon())
    {
        cout<<"Error: Failed to initialize al_init_image_addon!"<<endl;
        return -1;
    }

    display = al_create_display(width, height);
    if(!display)
    {
        cout<<"failed to create display!\n"<<endl;
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        cout<<"failed to create event_queue!\n"<<endl;
        al_destroy_display(display);
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        cout<<"failed to create timer!"<<endl;
    }

    if(!al_install_keyboard())
    {
        cout<<"failed to initialize the keyboard!"<<endl;
    }

    if(!al_install_audio() || !al_init_acodec_addon() || !al_reserve_samples(2))
    {
        cout<<"failed to initialize Audio!"<<endl;
    }

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    cout<<"Llego aki";
//    cartoonFont = al_load_ttf_font("GameFiles/fonts/kenpixel_blocks.ttf",50,0 );

    al_install_joystick();


    al_register_event_source(event_queue, al_get_display_event_source(display));//registrar eventos del display
    al_register_event_source(event_queue, al_get_timer_event_source(timer));//registrar eventos del timer
    al_register_event_source(event_queue, al_get_keyboard_event_source());//registrar eventos del teclado

    al_start_timer(timer);

    al_init_timeout(&timeout, 0.06);
}


bool rotated=false;

int main()
{
 // ALLEGRO_DISPLAY *display = NULL;

    alinit();
    al_reconfigure_joysticks();
    joystick=al_get_joystick(al_get_num_joysticks()-1);
    //joystick=al_get_joystick(0);
    fondo = al_load_bitmap("fondo.png");
    per= al_load_bitmap("charizard/cha.png");

    cout<<"   "<<endl;
    cout<<al_get_num_joysticks<<endl;
    cout<<al_get_joystick_num_buttons(joystick)<<endl;

    al_register_event_source(event_queue, al_get_joystick_event_source());

    while(salir){

         bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
         al_draw_bitmap(fondo,0,0,0);

        if(ev.keyboard.keycode== ALLEGRO_KEY_A){
            if(!rotated)
                rotated=true;
            else
                rotated=false;
        }

//         if( ev.type == ALLEGRO_EVENT_JOYSTICK_AXIS){
//            if(!rotated)
//                rotated=true;
//            else
//                rotated=false;
//        }
          if( ev.joystick.button== 1){
            if(!rotated)
                rotated=true;
            else
                rotated=false;
        }

//        if(ev.keyboard.keycode== ALLEGRO_KEY_A){
//        cout<<al_get_joystick_button_name(joystick,2)<<endl;
//            if(ev.joystick.button==2)
//            al_draw_rotated_bitmap(per,20,20,20,20,2,3);
//        }

        if(rotated){
            al_draw_rotated_bitmap(per,20,20,20,20,2,3);
        }

        else{
          al_draw_bitmap(per, 0, 0, 0);
        }


        if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
            salir=false;



        al_flip_display();
        //cout<<"hola"<<endl;



    }




   return 0;
}

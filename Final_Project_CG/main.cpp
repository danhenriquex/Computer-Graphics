// Include AssImp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include<cstdlib>

// Include GLEW
#include <GL/glew.h>

#include "display.h"
#include "object.h"
#include"objloader.h"

using namespace std;
using namespace glm;

int DISPLAY_WIDTH = 1080;
int DISPLAY_HEIGHT = 920;
bool isRunning = true;
bool up = false;
bool down = false;


float Ry_accel = 0.4f;
float teta = 0;
float teta1 = 0;
float eyeX = 0, eyeY = 0, eyeZ = 0, centerX = 0, centerY = 0, centerZ = 0;
int camera_style = 1;

vec3 camera;
vec3 pos(0.0f, 0.0f, 0.0f);
vec3 o(0.0f, 0.0f, -1.0f);
vec3 v(0.0f, 0.0f, 0.0f);
vec4 vel(0.0f, 0.0f, 0.0f, 1.0f);
vec4 ori(0.0f, 0.0f, -1.0f, 1.0f);
mat4 rot = mat4(1.0f);
mat4 rot_cam = mat4(1.0f);

vec3 pos_a(0.0f,0.0f,0.0f);

void processEvents(){
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0){
        switch (event.type){
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                //Eventod de tecla pressionada aqui
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    isRunning = false;
                }
                break;
            case SDL_KEYUP:
                //Eventod de tecla solta aqui
                break;
            case SDL_MOUSEBUTTONDOWN:
                //Eventos de botÃ£o do mouse pressionado aqui
                break;
            case SDL_MOUSEBUTTONUP:
                //Eventos de botÃ£o do mouse solto aqui
                break;
            case SDL_MOUSEMOTION:
                //Eventos de movimentaÃ§Ã£o do mouse aqui
                break;
            case SDL_MOUSEWHEEL:
                //Eventos de movimentaÃ§Ã£o da roldana do mouse aqui
                break;
            case SDL_WINDOWEVENT:
                break;
        }
    }
}

void control(){

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    double norma = sqrt(v.z*v.z + v.x*v.x);


    if (keys[SDL_SCANCODE_UP]){

        up = true;

        if(norma < 1.2){

            v.z = v.z + 0.02*o.z;
            v.x = v.x + 0.02*o.x;

            if(down){
                v.z = 0.4*v.z;
                v.x = 0.4*v.x;
            }

        }

        down = false;
    }else if (keys[SDL_SCANCODE_DOWN]){

        down = true;

        if(norma < 1.2){

            v.z = v.z - 0.02*o.z;
            v.x = v.x - 0.02*o.x;

            if(up){
                v.z = 0.4*v.z;
                v.x = 0.4*v.x;
            }
        }

        up = false;
    }else{

        v.z = 0.7*v.z;
        v.x = 0.7*v.x;

        if(norma < 0.0001){
            v.z = 0;
            v.x = 0;
        }
    }

    if (keys[SDL_SCANCODE_RIGHT]){

        vel.x = v.x;
        vel.z = v.z;

        ori.z = o.z;
        ori.x = o.x;
     if(norma != 0){
    	teta += radians(Ry_accel);
    }else{
        teta = 0;
    }
        rot = rotate(mat4(1.0f),teta,vec3(0.0f,1.0f,0.0f));

    	vel = vel * rot;
        ori = ori * rot;

        v.x = vel.x;
        v.z = vel.z;

        o.x = ori.x;
        o.z = ori.z;

    	o = normalize(o);

    }else if (keys[SDL_SCANCODE_LEFT]){

        vel.x = v.x;
        vel.z = v.z;

        ori.z = o.z;
        ori.x = o.x;
    if(norma != 0){
    	teta -= radians(Ry_accel);
    }else{
        teta = 0;
    }
    	rot = rotate(mat4(1.0f),teta,vec3(0.0f,1.0f,0.0f));

    	vel= vel * rot;
    	ori = ori * rot;


    	v.x = vel.x;
    	v.z = vel.z;

        o.x = ori.x;
        o.z = ori.z;

    	o = normalize(o);

    }else{
        teta = 0;
    }

    if(keys[SDL_SCANCODE_1]){
        camera_style = 1;

    }
    if(keys[SDL_SCANCODE_2]){
        camera_style = 2;
    }
    if(keys[SDL_SCANCODE_3]){
        camera_style = 3;
    }

}

int main(int argc, char** argv)
{

	object Car, road, grass, tree1, tree2;
	Car.import("Objetos/Car.obj");
    road.import("Objetos/road.obj");
    grass.import("Objetos/grass.obj");
    tree1.import("Objetos/tree.obj");
    tree2.import("Objetos/tree2.obj");

    Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

 ///define a luz
    float lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightAmbient[] = {4.0f, 4.0f, 4.0f, 1.0f};
    float lightPosition[]= {1.0f, 10.0f, 1.0f, 1.0f};

    float mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float mat_shininess[] = { 10.0f };  ///

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0,GL_AMBIENT, lightAmbient);

    glLightfv(GL_LIGHT0,GL_DIFFUSE, lightDiffuse);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);




	while(isRunning){

	//limpando a tela
	display.Clear(0.0f, 0.0f, 1.0f, 1.0f);

    processEvents();

    pos_a.x = pos.x;
    pos_a.z = pos.z;
	control();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0f,DISPLAY_WIDTH/DISPLAY_HEIGHT,1.1f,100.f);

	pos = pos - v;
    mat4 trans = translate(mat4(1.0f), pos);
    mat4 ModelCam  = rot_cam * trans ;
    camera = vec3( ModelCam * vec4(v.x, v.y, 0.0f + v.z, 1.0f));  //posiÃ§Ã£o da camera

    ///v = velocidade, pos = posição do carro
    if(camera_style == 1){
        eyeX = v.x+pos.x;
        eyeY = pos.y+v.y+6.0f;
        eyeZ = v.z+pos.z;
        centerX = pos.x;
        centerY = pos.y;
        centerZ = pos.z;
    }
    ///v = velocidade, pos = posição do carro
    else if(camera_style == 2){
        eyeX = pos.x;
        eyeY = pos.y+2.0f;
        eyeZ = pos.z-4.0f;
        centerX = v.x+pos.x;
        centerY = v.y+pos.y;
        centerZ = v.z+pos.z;
    }
    ///v = velocidade, pos = posição do carro
    else if(camera_style == 3){
        eyeX = 15.0f;
        eyeY = 6.0f;
        eyeZ = 15.0f;
        centerX = pos.x;
        centerY = pos.y;
        centerZ = pos.z;

    }
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0f, 1.0f, 0.0f); //
    //gluLookAt(0.0f,6.3f,30.0f, 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f);

    mat4 rot_origi = rotate(mat4(1.0f),-teta,vec3(0.0f,1.0f,0.0f));
    //teta =0;
    mat4 trans_origi = translate(mat4(1.0f), -pos_a);

    mat4 ModelCar = trans * rot_origi * trans_origi;

    if((pos.x > -18 && pos.x < 45.8) && (pos.z > -59.8 && pos.z < 16.8)){
        Car.tras(ModelCar);
    }else{
        v.x=0;
        v.z=0;
    }
	Car.drawObj();
    road.drawObj();
    grass.drawObj();
    tree1.drawObj();
    tree2.drawObj();

	display.SwapBuffers();


	}


return 0;
}

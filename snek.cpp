#include <cstdio>
#include <ctime>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace sf;

int score = 0;

SoundBuffer bafer;
Sound sound;
Music music;
Font font;
Text text;
Text help;
Text info;
   Texture texture;
        Texture kita;
        Texture kita2;
        Texture kita5;
struct Clanak {
    float x, y;
    static char smer;
    struct Clanak *sled, *pret;
} *glava;

char Clanak::smer;

struct Hrana {
float x,y;
}hrana;
typedef struct Clanak Clanak;

void food () {
    sound.play();
    srand(time(0));
hrana.x=rand()%(39+1);
hrana.x*=20;
hrana.y=rand()%(29+1);
hrana.y*=20;
fprintf(stderr,"%.2f %.2f\n",hrana.x,hrana.y);

}

bool pojedena() {

    return (glava->x==hrana.x)&&(glava->y==hrana.y);
}

void ispis () {
    Clanak *tek=glava;

    while(tek!=NULL){
        fprintf(stderr,"%.2f %.2f\n",tek->x,tek->y);
        tek=tek->sled;
    }
}

void init() {
     text.setFillColor(Color::Black);
    help.setString("Arsen Djurdjev & Nikola Grujicic 2018");
    info.setString("Version 1.04");
      kita5.loadFromFile("TEXTURE/kita2.png");
    
    if(!texture.loadFromFile("TEXTURE/kita.png")){
        fprintf(stderr, "lol\n");
    }
   
       if(score==0){
        kita.loadFromFile("TEXTURE/rep.png");
        
    }
   
    

          if(!kita2.loadFromFile("TEXTURE/kita3.png")){
        fprintf(stderr, "lol\n");
    }
    if (!font.loadFromFile("FONT/arial.ttf")) fprintf(stderr, "Nemre font\n");

    help.setFont(font);
    help.setCharacterSize(10);
    help.setPosition(250,580);


info.setFont(font);
info.setCharacterSize(10);
info.setPosition(730,580);

    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(0, 0);

    food();
    Clanak *tek;
    
    float step = 60;

    glava = new Clanak;
    tek=glava;
    glava->x = step;
    glava->y = 0;
    glava->sled=NULL;
    glava->pret=NULL;
    glava->smer='D';
    for(int i=0;i<3;i++){
        tek->sled=new Clanak;
        tek->sled->pret=tek;
        tek->sled->sled=NULL;
        tek=tek->sled;

        step -= 20;
        tek->x = step;
        tek->y = 0.f;
    }
}


void crtaj(RenderWindow& win){
      if(score==80){
        kita5.loadFromFile("TEXTURE/kita4.png");
        
    }
  
        Sprite gl(kita5);
        Sprite background(texture);
        Sprite krug(kita2);
        Sprite jelo(kita);
  //  CircleShape krug(10.f);

    win.clear();
    background.setPosition(0,0);
     win.draw(background);
      //krug.setRadius(7.f);
  //  krug.tre
    jelo.setPosition(hrana.x,hrana.y);
    win.draw(jelo);
   // krug.setFillColor(Color::Red);
   // krug.setRadius(10.f);
    Clanak *tek;
    tek=glava;
    int sdsd=0;
    while(tek!=NULL){
        
        if(sdsd==0){
            gl.setPosition(tek->x,tek->y);
            win.draw(gl);
            sdsd++;
            
        }
        else{
        krug.setPosition(tek->x,tek->y);
        win.draw(krug);
        
}
        tek=tek->sled;
    }    

    win.draw(text);
    win.draw(help);
    win.draw(info);
    win.display();
}

void dodajP(){
Clanak *tmp=new Clanak;

tmp->sled = glava;
glava->pret = tmp;
glava = tmp;

glava->pret=NULL;
glava->x=glava->sled->x;
glava->y=glava->sled->y;
}

void skiniK(){
    Clanak *tek=glava;

    while(tek->sled!=NULL){
        tek=tek->sled;
    }

    tek->pret->sled=NULL;
    delete tek;
}

void pomeriZmiju(char smer)
{
    switch(smer) {
    case 'W':
        if (!(glava->smer == 'S')) {
            dodajP();
            glava->y -= 20.f;
            glava->smer = 'W';
            if (!pojedena()) skiniK();
            else { food(); score++;}
        } break;

    case 'S':
        if (!(glava->smer == 'W')) {
            dodajP();
            glava->y += 20.f;
            glava->smer = 'S';
            if (!pojedena()) skiniK();
            else { food(); score++; }
        } break;

    case 'A':
        if (!(glava->smer == 'D')) {
            dodajP();
            glava->x -= 20.f;
            glava->smer = 'A';
            if (!pojedena()) skiniK();
            else { food(); score++; }
        } break;

    case 'D':
        if (!(glava->smer == 'A')) {
            dodajP();
            glava->x += 20.f;
            glava->smer = 'D';
            if (!pojedena()) skiniK();
            else { food(); score++; }
        }
    }

    Clanak *tek = glava->sled;
    while (tek != NULL) {
        if ((glava->x == tek->x) && (glava->y == tek->y)){
            fprintf(stderr,"ujeo se");
             music.stop();
             exit(0);
        
        }
        tek=tek->sled;
    }

    char buff[50];
    sprintf(buff, "Score: %3d", score);
    text.setString(buff);
   

    if (glava->x>780){
        glava->x=0;
         dodajP();
              if (!pojedena()) skiniK();
            else { food(); score++; }
    }
        else if (glava->x<0){
            glava->x=780;
             dodajP();
                  if (!pojedena()) skiniK();
            else { food(); score++; }
        }
        else if (glava->y<0){
            glava->y=580;
             dodajP();
                  if (!pojedena()) skiniK();
            else { food(); score++; }
        }
        else if (glava->y>580){
            glava->y=0;
             dodajP();
                  if (!pojedena()) skiniK();
            else { food(); score++; }
        }
    
    }


int main () {
    int vel=20;
    float f=0.08;
    init();
    RenderWindow window(VideoMode(800,600), "Snek 1.04");

    window.setFramerateLimit(60);
      
    Clock clock;

    if (!bafer.loadFromFile("SOUND/whip.wav")) fprintf(stderr,"Nemere\n");
    else sound.setBuffer(bafer);
    if (!music.openFromFile("SOUND/snd.ogg")) fprintf(stderr, "Nemere\n");
    else{
     music.play();
     music.setLoop(true);
    }

    clock.restart();
    while (window.isOpen())
    {
        Event event;

        while(window.pollEvent(event))
        {
            window.setKeyRepeatEnabled(false);
                  if (event.type == Event::Closed){
                window.close();
            }
        

            if (event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Escape){
                    window.close();
                }

                char s = 0;
                if(event.key.code == Keyboard::W){
                    if(glava->smer=='W'){
                        s=0;
                    }
                    else
                    s = 'W';
                    
                } else if(event.key.code == Keyboard::S){
                        if(glava->smer=='S'){
                        s=0;
                    }
                    else
                    s = 'S';   
                }  else if(event.key.code == Keyboard::A){
                        if(glava->smer=='A'){
                        s=0;
                    }
                    else
                    s = 'A';
                }  else if(event.key.code == Keyboard::D){
                        if(glava->smer=='D'){
                        s=0;
                    }
                    else
                    s = 'D';
                }

                if (s != 0) pomeriZmiju(s);

                //ispis();
                clock.restart();
            }
        }
        if((score==vel)&&(f>0.04)){
            f-=0.01;
            vel+=20;
            fprintf(stderr,"%f",f);

           
        }

        if (clock.getElapsedTime().asSeconds()>=f) {
            pomeriZmiju(glava->smer);
            clock.restart();
        }

        crtaj(window);
    }

    return 0;
}



/*Created by Nikola Grujicic, Arsen Djurdjev, 2018. Cross-platform support and optimizations maintained by A.Dj.*/
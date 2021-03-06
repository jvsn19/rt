//
// Created by unkwis on 03/12/16.
//

#include "SDL.h"
SDL::SDL(std::string path) {
    std::ifstream ifs;
    ifs.open (path, std::ifstream::in);
    this->supersampling = false;
    while(!ifs.eof()){
        if(ifs.peek() == '\n' || ifs.peek() == ' ') {
            ifs.get();
        }
        else if(ifs.peek() == '#'){
            ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            std::string tag;
            ifs >> tag;
            if(!tag.compare("output")){
                ifs >> this->output;
            }
            else if(!tag.compare(("eye"))){
                T3 eye = T3();
                ifs >> eye.x
                    >> eye.y
                    >> eye.z;
                this->eye = eye;
            }
            else if(!tag.compare("ortho")){
                Ortho ortho = Ortho();
                ifs >> ortho.x0
                    >> ortho.y0
                    >> ortho.x1
                    >> ortho.y1;
                this->ortho = ortho;
            }
            else if(!tag.compare(("size"))){
                Size size = Size();
                ifs >> size.w
                    >> size.h;
                this->size = size;
            }
            else if(!tag.compare("background")){
                Color background = Color();
                ifs >> background.r
                    >> background.g
                    >> background.b;
                this->background = background;
            }
            else if(!tag.compare("ambient")){
                ifs >> this->ambient;
            }
            else if(!tag.compare("light")){
                Light light = Light();
                ifs >> light.dir.x
                    >> light.dir.y
                    >> light.dir.z
                    >> light.intensity;
                this->lights.push_back(light);
            }
            else if(!tag.compare("supersample")) {
                std::string decisor;
                ifs >> decisor;
                decisor.compare("on") ? this->supersampling = false : this->supersampling = true;
            }
            else if(!tag.compare("profundidade")){
                ifs >> this->depth;
            }
            else if(!tag.compare("object")){
                string texPath;
                double a, b, c, d, e, f, g, h, j, k, red, green, blue, ka, kd, ks, n, KS, KT, ir;
                ifs >> a
                    >> b
                    >> c
                    >> d
                    >> e
                    >> f
                    >> g
                    >> h
                    >> j
                    >> k
                    >> red
                    >> green
                    >> blue
                    >> ka
                    >> kd
                    >> ks
                    >> n
                    >> KS
                    >> KT
                    >> ir
                    >> texPath;
                Texture *texture;
                if(texPath.compare("null")) texture = new Texture(texPath);
                else texture = nullptr;
                Color color = Color(red,green,blue);
                Object object = Object(a, b, c, d, e, f, g, h, j, k, ka, kd, ks, n, KS, KT, ir, color, texture);
                this->objects.push_back(object);
            }
        }
    }
    ifs.close();
}

std::string SDL::getOutput() {
    return this->output;
}

T3 SDL::getEye(){
    return this->eye;
}

Ortho SDL::getOrtho(){
    return this->ortho;
}

Size SDL::getSize(){
    return this->size;
}

Color SDL::getBackground(){
    return this->background;
}

double SDL::getAmbient(){
    return this->ambient;
}

std::vector<Light> SDL::getLights(){
    return this->lights;
}

bool SDL::getSuperSampling(){
    return this->supersampling;
}

int SDL::getDepth(){
    return this->depth;
}

std::vector<Object> SDL::getObjects(){
    return this->objects;
}
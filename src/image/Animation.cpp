#include "Animation.hpp"
#include "../gamestate/Window_Manager.hpp"

void Animation::load(sf::Texture& texture, int frame_width_p, int frame_height_p, int number_of_frames_p, int rect_y_p){
	frame_width=frame_width_p;
	frame_height=frame_height_p;
	number_of_frames=number_of_frames_p;
	rect_y=rect_y_p;


	for(int i=0;i<number_of_frames;i++){
		sprites.push_back(sf::Sprite());
		sprites[i].setTexture(texture,false);
		sprites[i].setTextureRect(sf::IntRect((i*frame_width),rect_y,frame_width,frame_height));
		sprites[i].setOrigin(frame_width/2,frame_height/2);
	}

}


void Animation::load(sf::Texture& texture, Animation_Blueprint blueprint){
	name=blueprint.get_name();
	frame_width=blueprint.get_frame_width();
	frame_height=blueprint.get_frame_height();
	rows=blueprint.get_rows();
	collumns=blueprint.get_collumns();
	number_of_frames=blueprint.get_number_of_frames();
	origin_x=blueprint.get_origin_x();
	origin_y=blueprint.get_origin_y();
	buffer_x=blueprint.get_buffer_x();
	buffer_y=blueprint.get_buffer_y();

	for(int i=0;i<rows;i++){
		for(int j=0;j<collumns;j++){
			if(i*collumns+j<number_of_frames){
				sprites.push_back(sf::Sprite());
				sprites[i*collumns+j].setTexture(texture,false);
				sprites[i*collumns+j].setTextureRect(sf::IntRect((j*(frame_width+buffer_x))+origin_x,(i*(frame_height+buffer_y))+origin_y,frame_width,frame_height));
				sprites[i*collumns+j].setOrigin(frame_width/2,frame_height/2);
				//std::cout<<name<<"f"<<(i*collumns+j)<<" i="<<i<<",h="<<frame_height<<",by="<<buffer_y<<",oy="<<origin_y<<std::endl;
			}
		}
	}
}

void Animation::set_position(int x_p, int y_p){
	for(int i=0;i<number_of_frames;i++){
		sprites[i].setPosition(x_p,y_p);
	}
}
void Animation::move(int x_p, int y_p){
	for(int i=0;i<number_of_frames;i++){
		sprites[i].move(x_p,y_p);
	}
}

void Animation::move(Point p_p){
	for(int i=0;i<number_of_frames;i++){
		sprites[i].move(p_p.get_x(),p_p.get_y());
	}
}


void Animation::set_h_mirror(bool b_p){
	if(mirrored!=b_p){
		mirrored=b_p;
		for(int i=0;i<number_of_frames;i++){
			sprites[i].scale(-1.0f,1.0f);
		}
	}
}
void Animation::animate(){
	if(!finished){
		float actual_fps=Window_Manager::get_execution_fps();
		if(recorded_fps!=actual_fps){
			fps_timer=fps_timer*(actual_fps/recorded_fps);
		}
		if(fps_timer<=0){
			current_frame++;
			recorded_fps=actual_fps;
			fps_timer=((float)recorded_fps/(float)desired_fps);
			//std::cout<<name<<"rc"<<recorded_fps<<"/ds"<<desired_fps<<"=t"<<fps_timer<<std::endl;
		}
		fps_timer--;
		

		if(current_frame==number_of_frames-1){
			if(!loop){
				finished=true;
			}
		}
		if(current_frame>=number_of_frames){
			current_frame=0;
		}
	}
}

sf::Sprite Animation::get_current_frame()const{
	if(!finished){
		return sprites[current_frame];
	}
	return sf::Sprite();
}
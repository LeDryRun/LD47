#include "Animation_Sheet.hpp"
#include <iostream>
#include <fstream>

Animation_Sheet::Animation_Sheet(std::string file_p, int f_w_p, int f_h_p, int a_l_p, int y_l_p, std::string name_p){
	load(file_p, f_w_p, f_h_p, a_l_p, y_l_p, name_p);
}
Animation_Sheet::Animation_Sheet(std::string file_p){
	load(file_p);
}

void Animation_Sheet::load(std::string file_p, int f_w_p, int f_h_p, int a_l_p, int y_l_p, std::string name_p){
	frame_width=f_w_p;
	frame_height=f_h_p;
	animation_length=a_l_p;
	sheet_y_length=y_l_p;
	name=name_p;

	texture.loadFromFile(file_p);
	texture.setSmooth(true);
}

void Animation_Sheet::load(std::string file_p){
	std::ifstream sheet_stream(file_p+".man");

	int max=100;
	char*raw;
	raw=(char*)malloc(max);

	int origin_y_cumulative=0;

	if(sheet_stream.is_open()){
		std::string n;
		int frame_w;
		int frame_h;
		int rows;
		int collumns;
		int number_of_frames;
		int origin_x;
		int origin_y;
		int buffer_x=0;
		int buffer_y=0;

		do{
			sheet_stream.get(raw,max,':');
			n=raw;
			sheet_stream.get();

			if(n=="buffer"){
				sheet_stream.get(raw,max,'x');
				buffer_x=atoi(raw);
				sheet_stream.get();
				sheet_stream.get(raw,max,'\n');
				buffer_y=atoi(raw);
				sheet_stream.get();
				origin_y_cumulative=buffer_y;
			}else{
				sheet_stream.get(raw,max,'x');
				frame_w=atoi(raw);
				sheet_stream.get();
				sheet_stream.get(raw,max,',');
				frame_h=atoi(raw);
				sheet_stream.get();

				sheet_stream.get(raw,max,'r');
				rows=atoi(raw);
				sheet_stream.get();
				sheet_stream.get(raw,max,'c');
				collumns=atoi(raw);
				sheet_stream.get();
				sheet_stream.get();

				sheet_stream.get(raw,max,'f');
				number_of_frames=atoi(raw);
				sheet_stream.get(raw,max,'\n');
				sheet_stream.get();

	//optional origns?
				origin_x=buffer_x;
				origin_y=origin_y_cumulative;
				origin_y_cumulative+=rows*(frame_h+buffer_y);

				//std::cout<<n<<":"<<frame_w<<"x"<<frame_h<<","<<rows<<"r"<<collumns<<"c"<<","<<number_of_frames<<"f,O="<<origin_x<<"x"<<origin_y<<",B="<<buffer_x<<"x"<<buffer_y<<std::endl;

				blueprints.push_back(Animation_Blueprint(n,frame_w,frame_h,rows,collumns,number_of_frames,origin_x,origin_y,buffer_x,buffer_y));
			}

		}while(!sheet_stream.eof());

	}else{
		std::cout<<"ERROR: failed to open file "<<file_p<<".man"<<std::endl;
	}
	/*for(int i=0;i<(int)blueprints.size();i++){
		std::cout<<blueprints.at(i).get_name()<<std::endl;
	}*/

	texture.loadFromFile(file_p+".png");
	texture.setSmooth(true);
}

bool Animation_Sheet::check_for_blueprint(Animation& animation){
	for(int i=0;i<(int)blueprints.size();i++){
		if(blueprints.at(i).get_name()==animation.get_name()){
			load_animation(animation,blueprints.at(i));
			return true;
		}
	}
	return false;
}

void Animation_Sheet::load_animation(Animation& animation, int y_p){
	animation.load(texture,frame_width,frame_height,animation_length,(y_p*(frame_height)));
}

void Animation_Sheet::load_animation(Animation& animation, Animation_Blueprint blue_p){
	animation.load(texture,blue_p);
}
#ifndef ANIMATION_BLUEPRINT
#define ANIMATION_BLUEPRINT

#include <string>

class Animation_Blueprint{
private:
	std::string name;
	int frame_width;
	int frame_height;
	int number_of_frames;
	int collumns;
	int rows;
	int origin_x;
	int origin_y;
	int buffer_x=0;
	int buffer_y=0;
public:
	Animation_Blueprint(){}
	Animation_Blueprint(std::string name_p, int frame_width_p, int frame_height_p, int rows_p, int collumns_p, int number_of_frames_p, int origin_x_p, int origin_y_p){
		create(name_p, frame_width_p, frame_height_p,rows_p,  collumns_p, number_of_frames_p, origin_x_p, origin_y_p,0,0);
	}
	Animation_Blueprint(std::string name_p, int frame_width_p, int frame_height_p, int rows_p, int collumns_p,
		 int number_of_frames_p, int origin_x_p, int origin_y_p, int buffer_x_p, int buffer_y_p){
		create(name_p, frame_width_p, frame_height_p,rows_p,  collumns_p, number_of_frames_p, origin_x_p, origin_y_p,buffer_x_p,buffer_y_p);
	}
	void create(std::string name_p, int frame_width_p, int frame_height_p, int rows_p, int collumns_p,
		 int number_of_frames_p, int origin_x_p, int origin_y_p, int buffer_x_p, int buffer_y_p){
		name=name_p;
		frame_width=frame_width_p;
		frame_height=frame_height_p;
		rows=rows_p;
		collumns=collumns_p;
		number_of_frames=number_of_frames_p;
		origin_x=origin_x_p;
		origin_y=origin_y_p;
		buffer_x=buffer_x_p;
		buffer_y=buffer_y_p;
	}
	std::string get_name(){return name;}
	int get_frame_width(){return frame_width;}
	int get_frame_height(){return frame_height;}
	int get_rows(){return rows;}
	int get_collumns(){return collumns;}
	int get_number_of_frames(){return number_of_frames;}
	int get_origin_x(){return origin_x;}
	int get_origin_y(){return origin_y;}
	int get_buffer_x(){return buffer_x;}
	int get_buffer_y(){return buffer_y;}
};

#endif
#include <fstream>

#include "page.h"

using std::endl;
using std::ofstream; //

class Board {
    public:
        Board(int num_jobs, int width, int height, ofstream& output_stream);
        ~Board();

        void print_board();
        void print_job(int job_idx, char job_type, int id);

        //job functions
        void insert_page(int x, int y, int width, int height, int id, int content);
        void delete_page(int id);
        void modify_content(int id, char content);
        void modify_position(int id, int x, int y);

    private:
        int num_jobs, width, height; 
        ofstream& output; 
        char* board; 
};


Board::Board(int num_jobs, int width, int height, ofstream& output_stream): output(output_stream) {
    this->width = width;
    this->height = height;
    this->num_jobs = num_jobs;

    board = new char[width*height];

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            board[h*width + w] = ' ';
        }
    }

}

Board::~Board() {
    delete board;
    
}


void Board::print_board() {
    int h, w;
    for (w = 0; w < width+2; w++) output << "- ";
    output << endl;
    
    for (h = 0; h < height; h++) {
        output << "| ";
        for (w = 0; w < width; w++) {
            output << board[h*width + w] << " ";
        }
        output << "| " << endl;
    }

    for (w = 0; w < width+2; w++) output << "- ";
    output << endl;
}

void Board::print_job(int job_idx, char job_type, int id) {
    output << ">> (" << job_idx <<") ";
    switch(job_type) {
        
        case 'i':
            output << "Insert ";
            break;
        case 'd':
            output << "Delete ";
            break;
        case 'm':
            output << "Modify ";
            break;
    }

    output << id << endl;
}


void Board::insert_page(int x, int y, int width, int height, int id, int content) {
    // //int -> char 로 변경
    // // 페이지에 추가하기
    // // Page pid;
    // // pid.x = x;
    // // pid.y = y;
    // // pid.width = width;
    // // pid.height = height;
    // // pid.id = id;
    // // pid.content = content;

    // 줄기 만들기
    // int page_c[num_jobs][num_jobs]; 관리할 차트, -1로 채우기
    // int num_r = 0; 뿌리 갯수
    // bool overlap = false;
    // for(int i=0; i<width; i++)
    // {
    //     for(int j=0; j<height; j++)
    //     {
    //         if(board[(x+i)*(y+j)] != " ")
    //         {
    //             overlap = true;
    //             어디랑 겹쳤는지 찾기
    //             int over_id = 겹친 아이디
    //             break;
    //         }
    //     }
    // }
    // if(overlap == false) 새로운 줄기 생성
    // {
    //     num_r +=1;
    //     page_c[num_r+1][0] = id;
    // }
    // else
    // {
    //     좀더 생각...
    // }

    // for(int i=0; i<width; i++)
    // {
    //     for(int j=0; j<height; j++)
    //     {
    //         output << board[(x+i)*(y+j)] << content;
    //     }
    // }
    // print_board();

}

void Board::delete_page(int id) {
    
}

void Board::modify_content(int id, char content) {
   

}
void Board::modify_position(int id, int x, int y) {
   
    
}

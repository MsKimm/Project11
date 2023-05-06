#include <fstream>

#include "page.h"

using std::endl;
using std::ofstream; 

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
        vector <Page> p_v;
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
    Page p(x, y, width, height, id, content);

    for (int i = 0; i < p_v.size(); i++) {
        for (int j = y; j < y+height; j++) {
            for (int k = x; k < x+width; k++) {
                if (board[width * y + x] == p_v[i].getcont()) {
                    p_v[i].set_vec(p.getid());
                }
            }
        }
        sort(p_v[i].begin(), p_v[i].end());
        unique(p_v[i].begin(), p_v[i].end());
        //오름차순

        //조건 : 각 페이지에 접근한 다음, 현재 페이지의 아래에 있다면 above 벡터에 하나씩 넣음.
        //페이지를 찾았다 -> p.set_vec(p1.getid());
    }
    p_v.push_back(p);
    //현재 페이지를 그림 -- **
    for (int j = y; j < y+height; j++) {
            for (int k = x; k < x+width; k++) {
                board[width * y + x] = content;
            }
            
    }
    print_board();
}

void Board::delete_page(int id) {   //8

    vector <int> temp_vec;
 
    for (int i = 0; i < p_v.size(); i++) {
        if (p_v[i].getid() == id) {
            temp_vec = p_v[i].get_vec();   // 그 페이지의 above 를 가져옴
        }
    }
    if (temp_vec.empty()) {
        //보드에서 해당 페이지를 지워준다.
        
    }
    for (int i = 0; i < temp_vec.size(); i++) {
        delete_page(temp_vec[i]);
    }
    
    //delete_board(id);
    //for (i=make_l-2; i>=0; i++)
    //{
    //    insert_page(make_l[i]);
    //}
    

}

void Board::modify_content(int id, char content) {
Page p(int x,int y,int width,int height,int id, content);
for(int i=0; i<p_v.size(); i++ )
{
    if(p_v[i].getid() == id)
    {
        p = p_v[i];
    }
}

//delete_board(id);
//insert_page(p.getX(), p.getY(), p.getW(), p.getH(), p.getid, content)
    //for (i=make_l-2; i>=0; i++)
    //{
    //    insert_page(make_l[i]);
    //}
}
void Board::modify_position(int id, int x, int y) {
   Page p(x, y, width, height, id, content);
for(i=0; i<p_v.size(); i++ )
{
    if(p_v[i].getid() == id)
    {
        p = p_v[i];
    }
}
    //delete_board
    //insert_page(x,y, p.getW(), p.getH(), p.getid, p.getcont)
    //for (i=make_l-2; i>=0; i++)
    //{
    //    insert_page(make_l[i]);
    //}
}

//void Board::add_board(i)
//if (p_v[id].size() == 0)
//{
// for (int j = y; j < y+height; j++) {
//          for (int k = x; k < x+width; k++) {
//             board[width * y + x] = p.content;
//     }
//}
//}
//for(int i=0; i<p_v[id]; i++)
//{
//add_board(i);
//}

// 또는 print_above : 모든 벡터 출력(above 와 함깨)

//void Board::delete_board(int id)
//{
//vector make_l; 순서 기록할 벡터
//if (p_v[id].size() == 0)
//{
//    above에서 그 숫자 제거
//    add_board() - 전체
//    make_l.push_back(id);
//    print_board();
//}
//for(i=p_v[id].size()-1; i>=0; i--)
//{
//    delete_board(p_v[i].getid());
//}
//}



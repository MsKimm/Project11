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

        //made functions
        void Board::add_board();
        void Board::delete_board(int id);
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

void Board::delete_page(int id) {
    delete_board(id);
    for(int i=0; i<p_v.size(); i++) //p_v에서 지운 아이디를 삭제한다.
    {
        if(p_v[i].id == id)
        {
            p_v.erase(p_v.begin() + i);
        }
        break;
    }
    make_l.pop_back(); //맨뒤의 id는 다시 만들게 아니므로 제거
    for(int i=make_l.size()-1; i>=0; i--)
    {
        insert_page(make_l[i].x, make_l[i].y, make_l[i].width, make_l[i].height, make_l[i].id, make_l[i].content);
        make_l.pop_back();
    }
}

void Board::modify_content(int id, char content) {
    int target;
    delete_board(id);
    for(int i=0; i<p_v.size(); i++) //p_v에서 지운 아이디를 삭제한다.
    {
        if(p_v[i].id == id)
        {
            target = i;
            p_v[i].content = content;
        }
        break;
    }
    insert_page(p_v[target].x, p_v[target].y, p_v[target].width, p_v[target].height, p_v[target].id, p_v[target].content);
    make_l.pop_back(); //맨뒤의 id는 다시 만들게 아니므로 제거
    for(int i=make_l.size()-1; i>=0; i--)
    {
        insert_page(make_l[i].x, make_l[i].y, make_l[i].width, make_l[i].height, make_l[i].id, make_l[i].content);
        make_l.pop_back();
    }
}
void Board::modify_position(int id, int x, int y) {
    int target;
    delete_board(id);
    for(int i=0; i<p_v.size(); i++) //p_v에서 지운 아이디를 삭제한다.
    {
        if(p_v[i].id == id)
        {
            target = i;
            p_v[i].x = x;
            p_v[i].y = y;
        }
        break;
    }
    insert_page(p_v[target].x, p_v[target].y, p_v[target].width, p_v[target].height, p_v[target].id, p_v[target].content);
    make_l.pop_back(); //맨뒤의 id는 다시 만들게 아니므로 제거
    for(int i=make_l.size()-1; i>=0; i--)
    {
        insert_page(make_l[i].x, make_l[i].y, make_l[i].width, make_l[i].height, make_l[i].id, make_l[i].content);
        make_l.pop_back();
    }
}

void Board::add_board()
{
    for(int i=0; i<p_v.size(); i++)
    {
        for (int j = p_v[i].y; j < p_v[i].y+height; j++) {
            for (int k = p_v[i].x; k < p_v[i].x+width; k++) 
            {
                board[width * p_v[i].y + p_v[i].x] = p_v[i].content;
            }
            
        }
    }
}


void Board::delete_board(int id)
{
if (p_v[id].size() == 0)
{
// 모든 above에서 그 숫자 제거
   for(int i=0; i<p_v.size(); i++)
   {
    p_v[i].above.erase(std::remove(p_v[i].above.begin(), p_v[i].above.end(), id), p_v[i].above.end());
    add_board();
    make_l.push_back(p_v[id]);
    print_board();
   }
}
else{
for(int i=0; i<p_v[id].above.size(); i++)
{
   delete_board(p_v[i].getid());
}
}
}



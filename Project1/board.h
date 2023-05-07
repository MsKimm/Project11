#include <fstream>
#include <vector>
#include "page.h"

using namespace std;
using std::endl;
using std::ofstream;

class Board {
public:

    std::vector <Page> p_v;
    std::vector <Page> make_l;

    Board(int num_jobs, int width, int height, ofstream& output_stream);
    ~Board();

    void print_board();
    void print_job(int job_idx, char job_type, int id);

    //job functions
    void insert_page(int x, int y, int width, int height, int id, char content);
    void delete_page(int id);
    void modify_content(int id, char content);
    void modify_position(int id, int x, int y);

    //made functions
    void add_board();
    void delete_board(int id);

    int num_jobs, width, height;
    ofstream& output;
    char* board;

    
private:

};


Board::Board(int num_jobs, int width, int height, ofstream& output_stream) : output(output_stream) {
    this->width = width;
    this->height = height;
    this->num_jobs = num_jobs;

    board = new char[width * height];

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            board[h * width + w] = ' ';
        }
    }

}

Board::~Board() {
    delete board;

}


void Board::print_board() {
    int h, w;
    for (w = 0; w < width + 2; w++) output << "- ";
    output << endl;

    for (h = 0; h < height; h++) {
        output << "| ";
        for (w = 0; w < width; w++) {
            output << board[h * width + w] << " ";
        }
        output << "| " << endl;
    }

    for (w = 0; w < width + 2; w++) output << "- ";
    output << endl;
}

void Board::print_job(int job_idx, char job_type, int id) {
    output << ">> (" << job_idx << ") ";
    switch (job_type) {

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


void Board::insert_page(int x, int y, int w, int h, int id, char content) {
    Page p(x, y, w, h, id, content);

    for (int i = 0; i < p_v.size(); i++) {
        for (int j = y; j < y + h; j++) {
            for (int k = x; k < x + w; k++) {
                if (board[width * j + k] == p_v[i].getcont()) {
                    p_v[i].above.push_back(p_v[i].id);
                }
            }
        }
        sort(p_v[i].above.begin(), p_v[i].above.end());
        unique(p_v[i].above.begin(), p_v[i].above.end());
        //오름차순

        //조건 : 각 페이지에 접근한 다음, 현재 페이지의 아래에 있다면 above 벡터에 하나씩 넣음.
        //페이지를 찾았다 -> p.set_vec(p1.getid());
    }
    int s = p_v.size();
    p_v.push_back(p); // 새로운 Page 객체 추가
    p_v[s].above = {}; // 추가한 객체의 above 벡터에 값 할당
    //현재 페이지를 그림 -- **
    for (int j = y; j < y + h; j++) {
        for (int k = x; k < x + w; k++) {
            board[width * j + k] = content;
        }

    }
    print_board();
    
}

void Board::delete_page(int id) {
    delete_board(id);
    make_l.pop_back(); //맨뒤의 id는 다시 만들게 아니므로 제거
    for (int i = make_l.size() - 1; i >= 0; i--)
    {
        insert_page(make_l[i].x, make_l[i].y, make_l[i].width, make_l[i].height, make_l[i].id, make_l[i].content);
        print_board();
    }
    make_l.clear();
}

void Board::modify_content(int id, char content) {
    int target;
    delete_board(id);
    for (int i = 0; i < p_v.size(); i++) //p_v에서 지운 아이디를 삭제한다.
    {
        if (p_v[i].id == id)
        {
            target = i;
            p_v[i].content = content;
        }
        
    }
    insert_page(p_v[target].x, p_v[target].y, p_v[target].width, p_v[target].height, p_v[target].id, p_v[target].content);
    make_l.pop_back(); //맨뒤의 id는 다시 만들게 아니므로 제거
    for (int i = make_l.size() - 1; i >= 0; i--)
    {
        insert_page(make_l[i].x, make_l[i].y, make_l[i].width, make_l[i].height, make_l[i].id, make_l[i].content);
    }
    make_l.clear();
}
void Board::modify_position(int id, int x, int y) {
    int target;
    delete_board(id);
    for (int i = 0; i < p_v.size(); i++) //p_v에서 지운 아이디를 삭제한다.
    {
        if (p_v[i].getid() == id)
        {
            target = i;
            p_v[i].x = x;
            p_v[i].y = y;
        }
    }
    insert_page(p_v[target].getX(), p_v[target].getY(), p_v[target].getW(), p_v[target].getH(), p_v[target].getid(), p_v[target].getcont());
    make_l.pop_back(); //맨뒤의 id는 다시 만들게 아니므로 제거
    for (int i = make_l.size() - 1; i >= 0; i--)
    {
        insert_page(make_l[i].x, make_l[i].y, make_l[i].width, make_l[i].height, make_l[i].id, make_l[i].content);
    }
    make_l.clear();
}

void Board::add_board()
{
    for (int i = 0; i < p_v.size(); i++)
    {
        for (int j = p_v[i].y; j < p_v[i].y + height; j++) {
            for (int k = p_v[i].x; k < p_v[i].x + width; k++)
            {
                board[width * j + k] = p_v[i].content;
            }

        }
    }
}

void Board::delete_board(int id)
{
    int target_id = -1;
    for(int i = 0; i < p_v.size(); i++)
    {
        if(id == p_v[i].id)
        {
            target_id = i;
            break;
        }
    }

    if (p_v[target_id].above.size() == 0)
    {
        make_l.push_back(p_v[target_id]); // 삭제 대상 Page를 make_l에 추가
        // 모든 above에서 그 숫자 제거
        for (int i = 0; i < p_v.size(); i++)
        {
            p_v[i].above.erase(std::remove(p_v[i].above.begin(), p_v[i].above.end(), id), p_v[i].above.end());
        }
        //p_v에서 없애기
        p_v.erase(p_v.begin() + target_id);
        add_board();
        print_board();
    }
    else {
        for (int i = 0; i < p_v[target_id].above.size(); i++)
        {
            delete_board(p_v[target_id].above[i]);
        }
    }
}








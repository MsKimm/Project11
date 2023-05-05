#include <vector>
#include <algorithm>

class Page {
public:
    int getX() { return x;}
    int getY() { return y; }
    int getW() { return width; }
    int getH() { return height; }
    int getid() { return id; }
    char getcont() { return content; }
    vector<int>& get_vec() { return above; }
    void set_vec(int a) { above.push_back(a); }
    void asd_vec() { sort(above.begin(), above.end()); }//오름차순
    void des_vec() { reverse(above.begin(), above.end()); }//내림차순

    Page(int x, int y, int width, int height, int id, int content)
        : x(x), y(y), width(width), height(height), id(id), content(content) {}


private:
    vector <int> above;
    int x, y; // position of the page on the board
    int width, height; // width and height of the page 
    int id; // unique id for each page
    char content;
};

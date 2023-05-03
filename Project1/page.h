class Page {
    public:
    int getX() { return x;}
    int getY() { return y; }
    int getW() { return width; }
    int getH() { return height; }
    int getid() { return id; }
    int getcont() { return content; }
    private:
        int x, y; // position of the page on the board
        int width, height; // width and height of the page 
        int id; // unique id for each page
        char content; 
};

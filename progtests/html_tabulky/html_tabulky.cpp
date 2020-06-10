#ifndef __PROGTEST__
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

/**
 * @brief	The central abstract class that represents Cell, also stores and processes information about each object.
 */
class CCell
{
public:
    /**
	 * @brief	Standard default constructor initializing an object - CCell
	 */
    CCell();
    /**
	 * @brief	Standard default destructor destructing an object - CCell
	 */
    virtual ~CCell();
    /**
	 * @brief								Virtual abstract method that creates the output for objects
	 * @param[in] ostringstream &oss		standard string stream output
	 * @param[in] int row			        variable for row
	 * @param[in] int maxwidth			    maximal width of cell where we putting data
	 * @param[in] int maxheight			    maximal height of cell where we putting data
	 */
    virtual void output(ostringstream &oss, int row, int maxwidth, int maxheight) = 0;
    /**
	 * @brief								Virtual abstract method that sets actual width and height of cell
	 */
    virtual void set_width_height() = 0;
    /**
	 * @brief								Virtual abstract method that makes copy of an object
     * @return                              an a copy of an object
	 */
    virtual CCell* clone() = 0;
    /**
	 *  @brief								getter for width
     *  @return								width of cell
	 */
    int getWidth();
    /**
	 *  @brief								getter for height
     *  @return								height of cell
	 */
    int getHeight();
protected:
    int width;
    int height;
};

CCell::~CCell()
{

}

CCell::CCell()
{
    width = 0;
    height = 0;
}

int CCell::getWidth()
{
    return width;
}

int CCell::getHeight()
{
    return height;
}

/**
 * @brief	The class that represents one of the varieties of the parent class CCell - CEmpty
 */
class CEmpty : public CCell
{
public:
    /**
	 * @brief	Standard default constructor initializing an object - CEmpty
	 */
    CEmpty();
    /**
	 * @brief	Standard default destructor destructing an object - CEmpty
	 */
    ~CEmpty();
    /**
    * @brief
    * @param[in]
    * @return
    */
    CEmpty& operator= (const CEmpty& x);
    /**
	 * @brief								Virtual method that makes copy of an object CEmpty
     * @return                              an a deep copy of an object CEmpty
	 */
    CCell* clone();
    /**
	 * @brief								Virtual method that creates the output for objects CEmpty
	 * @param[in] ostringstream &oss		standard string stream output
	 * @param[in] int row			        variable for row
	 * @param[in] int maxwidth			    maximal width of cell where we putting data
	 * @param[in] int maxheight			    maximal height of cell where we putting data
	 */
    void output(ostringstream &oss, int row, int maxwidth, int maxheight);
    /**
	 * @brief								Virtual method that sets actual width and height of cell for CEmpty objects
	 */
    void set_width_height();
};

CEmpty::CEmpty()
{
}

CEmpty::~CEmpty()
{
}

void CEmpty::set_width_height()
{
}

void CEmpty::output(ostringstream &oss, int row, int maxwidth, int maxheight)
{
    for(int i = 0; i < maxwidth; i++)
    {
        oss << ' ';
    }
}

CEmpty& CEmpty::operator= (const CEmpty& x)
{
    this->width = x.width;
    this->height = x.height;
    return *this;
}

CCell* CEmpty::clone()
{
    CEmpty *empty = new CEmpty;
    empty->height = dynamic_cast<CEmpty*>(this)->height;
    empty->width = dynamic_cast<CEmpty*>(this)->width;
    return empty;
}


/**
 * @brief	The class that represents one of the varieties of the parent class CCell - CText
 */
class CText : public CCell
{

public:
    /**
     * @brief	The enum that represents two types of aligns
     */
    enum aligns { ALIGN_LEFT, ALIGN_RIGHT };
    /**
	 * @brief	Standard default constructor initializing an object - CText
	 */
    CText();
    /**
	 * @brief	Constructor initializing an object - CText
     * @param[in] const string& x		    text to
     * @param[in] aligns align		        align of the text
	 */
    CText(const string& text, aligns align);
    /**
	 * @brief								Method that sets a text to an object CText
     * @param[in] const string& x		    text to
     * @return                              an object of itself
	 */
    CText& SetText(const string& text);
    /**
	 * @brief								Operator that equate an object CText to another CText
	 * @param[in] const CText& x		    object of CText
	 * @return                              an object of itself
	 */
    CText& operator= (const CText& x);
    /**
	 * @brief								Virtual method that makes copy of an object CText
     * @return                              an a deep copy of an object CText
	 */
    CCell* clone();
    /**
	 * @brief								Virtual method that creates the output for objects CText
	 *
	 * @param[in] ostringstream &oss		standard string stream output
	 * @param[in] int row			        variable for row
	 * @param[in] int maxwidth			    maximal width of cell where we putting data
	 * @param[in] int maxheight			    maximal height of cell where we putting data
	 */
    void output(ostringstream &oss, int row, int maxwidth, int maxheight);
    /**
	 * @brief								Virtual method that sets actual width and height of cell for CEmpty objects
	 */
    void set_width_height();
private:
    vector <string> text;
    aligns align;
};

CText::CText() : CCell()
{
    width = 0;
    height = 0;
}

CText::CText(const string& text, aligns align) : CCell()
{
    //this->text = text;
    string temp;
    bool flag = false;
    for(auto act = text.cbegin(); act != text.cend(); act++)
    {

        if((*act) == '\n')
        {
            flag = true;
            this->text.push_back(temp);
            temp = "";
            continue;
        }
        flag = false;
        temp += (*act);
    }
    if(!flag) this->text.push_back(temp);
    this->align = align;
}

void CText::output(ostringstream &oss, int row, int maxwidth, int maxheight)
{
    if(row >= (int)text.size())
    {
        for(int i = 0; i < maxwidth; i++)
        {
            oss << ' ';
        }
        return;
    }
    int shift = maxwidth - text[row].length();
    switch(align)
    {
        case ALIGN_LEFT:
        {

            oss << text[row];
            for(int i = 0; i < shift; i++)
            {
                oss << ' ';
            }
            break;
        }
        case ALIGN_RIGHT:
        {
            for(int i = 0; i < shift; i++)
            {
                oss << ' ';
            }
            oss << text[row];
            break;
        }
    }
}

void CText::set_width_height()
{
    int h = text.size();
    int w = 0;
    for(auto i = text.begin(); i != text.end(); i++)
    {
        if((int)(*i).length() > w) w = (*i).length();
    }
    if(w > width) width = w;
    if(h > height) height = h;
}

CText& CText::SetText(const string& text)
{
    this->text.clear();
    string temp;
    bool flag = false;
    for(auto act = text.cbegin(); act != text.cend(); act++)
    {

        if((*act) == '\n')
        {
            flag = true;
            this->text.push_back(temp);
            temp = "";
            continue;
        }
        flag = false;
        temp += (*act);
    }
    if(!flag) this->text.push_back(temp);
    return *this;
}

CText& CText::operator= (const CText& x)
{
    this->text = x.text;
    this->width = x.width;
    this->height = x.height;
    this->align = x.align;
    return *this;
}

CCell* CText::clone()
{
    CText *text = new CText;
    text->text = dynamic_cast<CText*>(this)->text;
    text->align = dynamic_cast<CText*>(this)->align;
    text->height = dynamic_cast<CText*>(this)->height;
    text->width = dynamic_cast<CText*>(this)->width;
    return text;
}

/**
 * @brief	The class that represents one of the varieties of the parent class CCell - CImage
 */
class CImage : public CCell
{
public:
    /**
	 * @brief	Standard default constructor initializing an object - CImage
	 */
    CImage();
    /**
	 * @brief								Method that adding another row to an object CImage
	 * @param[in] string row		        standard string that represent row of an image
	 * @return                              an object of itself
	 */
    CImage& AddRow(string row);
    /**
	 * @brief								Operator that equate an object CImage to another CImage
	 * @param[in] const CImage& x		    object of CImage
	 * @return                              an object of itself
	 */
    CImage& operator= (const CImage& x);
    /**
	 * @brief								Virtual method that makes copy of an object CImage
     * @return                              an a deep copy of an object CImage
	 */
    CCell* clone();
    /**
	 * @brief								Virtual method that creates the output for objects CImage
	 *
	 * @param[in] ostringstream &oss		standard string stream output
	 * @param[in] int row			        variable for row
	 * @param[in] int maxwidth			    maximal width of cell where we putting data
	 * @param[in] int maxheight			    maximal height of cell where we putting data
	 */
    void output(ostringstream &oss, int row, int maxwidth, int minwidth);
    /**
	 * @brief								Virtual method that sets actual width and height of cell for CImage objects
	 */
    void set_width_height();
private:
    vector<string> image;
};

CImage::CImage()
{
    width = 0;
    height = 0;
}




void CImage::output(ostringstream &oss, int row, int maxwidth, int maxheight)
{
    int shift_width = (maxwidth - width) / 2;
    int shift_height = (maxheight - height) / 2;
    if(row < shift_height || row >= shift_height + height)
    {
        for(int i = 0; i < maxwidth; i++)
        {
            oss << ' ';
        }
    }
    else
    {
        for(int i = 0; i < shift_width; i++) oss << ' ';
        oss << image[row - shift_height];
        if((maxwidth - width)%2 == 1) for(int i = 0; i < shift_width + 1; i++) oss << ' ';
        else for(int i = 0; i < shift_width; i++) oss << ' ';
    }
}

void CImage::set_width_height()
{
    for(auto it = image.begin(); it != image.end(); it++)
    {
        if((int)(*it).length() > width) width = (*it).length();
    }
    if((int)image.size() > height) height = image.size();
}

CImage& CImage::AddRow(string row)
{
    image.push_back(row);
    // set_width_height();
    return *this;
}

CImage& CImage::operator= (const CImage& x)
{
    this->image = x.image;
    this->width = x.width;
    this->height = x.height;
    return *this;
}

CCell* CImage::clone()
{
    CImage *image = new CImage;
    image->height = dynamic_cast<CImage*>(this)->height;
    image->width = dynamic_cast<CImage*>(this)->width;
    image->image = dynamic_cast<CImage*>(this)->image;
    return image;
}

/**
 * @brief	The class that represents table that working with cells
 */
class CTable
{
public:
    /**
      * @brief	Constructor initializing an object - CTable
      * @param[in] unsigned int rows		    rows of the table
      * @param[in] unsigned int cols		    columns of the table
      */
    CTable(unsigned int rows, unsigned int cols);
    /**
	 * @brief	Copy constructor initializing an object - CTable
     * @param[in] CTable &table	            object of CTable that will be copied
	 */
    CTable(CTable &table);
    /**
	 * @brief	Standard default destructor destructing an object - CTable
	 */
    ~CTable();
    /**
    * @brief	Method that sets an a cell with CCell object
    * @param[in] unsigned int row		    row of the cell to set
    * @param[in] unsigned int col		    column of the cell to set
    * @param[in] CCell &new_cell	        object of CCell to set to cell
    */
    void			    SetCell		(unsigned int row, unsigned int col, CCell &new_cell);
    /**
	 * @brief	Method that sets an a cell with CText object
     * @param[in] unsigned int row		    row of the cell to set
     * @param[in] unsigned int col		    column of the cell to set
     * @param[in] CText new_cell	        object of CText to set to cell
	 */
    void				SetCell		(unsigned int row, unsigned int col, CText  new_cell);
    /**
	 * @brief	Method that sets an a cell with CText object
     * @param[in] unsigned int row		    row of the cell to set
     * @param[in] unsigned int col		    column of the cell to set
     * @param[in] CImage new_cell	        object of CImage to set to cell
	 */
    void				SetCell		(unsigned int row, unsigned int col, CImage new_cell);
    /**
	 * @brief	Method that sets an a cell with CText object
     * @param[in] unsigned int row		    row of the cell to set
     * @param[in] unsigned int col		    column of the cell to set
     * @param[in] CEmpty new_cell	        object of CEmpty to set to cell
	 */
    void				SetCell		(unsigned int row, unsigned int col, CEmpty new_cell);
    /**
	 * @brief	Method that gets an a cell
     * @param[in] unsigned int row		    row of the cell to get
     * @param[in] unsigned int col		    column of the cell to get
     * @return 	                            object of CCell
	 */
    CCell&				GetCell		(unsigned int row, unsigned int col);
    /**
	 * @brief	Method that sets max heights and widthes of all columns an rows
	 */
    void                SetMaxWidthMaxHeight();
    /**
	 * @brief	Operator that makes standard string stream output
     * @param[in] ostringstream &oss		standard string stream to make output
     * @param[in] CTable& table		        table to output
     * @return 	                            standard string stream
	 */
    friend ostringstream&		operator<<	(ostringstream &oss, CTable& table);
    /**
	 * @brief								Operator that equate an object CTable to another CTable
	 * @param[in] const CImage& x		    object of CTable
	 * @return                              an object of itself
	 */
    CTable& operator= (const CTable& x);
    /**
	 *  @brief								Const getter for rows
     *  @return								rows of table
	 */
    unsigned int getRows() const;
    /**
	 *  @brief								Const getter for columns
     *  @return								columns of table
	 */
    unsigned int getCols() const;

private:
    unsigned int rows;
    unsigned int cols;
    vector <int> max_width;
    vector <int> max_height;
    vector <vector<CCell*>> table;

};

CTable					::	CTable		(unsigned int rows, unsigned int cols)
{
    this->rows = rows;
    this->cols = cols;
    for (size_t r = 0; r < rows; r++)
    {
        vector<CCell*> l;
        for (size_t c = 0; c < cols; c++)
        {
            CEmpty empty;
            CCell *cell = new CEmpty;
            l.push_back(cell);
        }
        table.push_back(l);
    }

    for(unsigned int i = 0; i < rows; i++) max_height.push_back(0);
    for(unsigned i = 0; i < cols; i++) max_width.push_back(0);
}

CTable::CTable(CTable &table)
{

    this->table.clear();
    this->rows = table.rows;
    this->cols = table.cols;
    this->max_width = table.max_width;
    this->max_height = table.max_height;
    for(auto it1 = table.table.begin(); it1 != table.table.end(); it1++)
    {
        vector<CCell*> push;
        for(auto it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
        {
            push.push_back((*it2)->clone());
        }
        this->table.push_back(push);
    }
}

CTable::~CTable()
{
    for (size_t r = 0; r < rows; r++)
    {
        for (size_t c = 0; c < cols; c++)
        {
            if(table[r][c]) delete table[r][c];
        }
        table[r].clear();
    }
    table.clear();
}



CCell&			CTable	::	GetCell		(unsigned int row, unsigned int col)
{
    return *table[row][col];
}
void			CTable	::	SetCell		(unsigned int row, unsigned int col, CCell &new_cell)
{
    if(table[row][col] == &new_cell) return;
    if(table[row][col]) delete table[row][col];
    table[row][col] = new_cell.clone();
}

void			CTable	::	SetCell		(unsigned int row, unsigned int col, CEmpty new_cell)
{

    if(table[row][col]) delete table[row][col];
    table[row][col] = new_cell.clone();
}

void			CTable	::	SetCell		(unsigned int row, unsigned int col, CText new_cell)
{
    if(table[row][col]) delete table[row][col];
    table[row][col] = new_cell.clone();
}

void			CTable	::	SetCell		(unsigned int row, unsigned int col, CImage new_cell)
{
    if(table[row][col]) delete table[row][col];
    table[row][col] = new_cell.clone();
}

unsigned int CTable::getRows() const
{
    return rows;
}

unsigned int CTable::getCols() const
{
    return cols;
}

void                CTable::SetMaxWidthMaxHeight()
{
    for(unsigned int r = 0; r < rows; r++)
    {
        for(unsigned int c = 0; c < cols; c++)
        {
            table[r][c]->set_width_height();
        }
    }
    for(unsigned int r = 0; r < rows; r++)
    {
        max_height[r] = 0;
    }
    for(unsigned int c = 0; c < cols; c++)
    {
        max_width[c] = 0;
    }
    for(unsigned int r = 0; r < rows; r++)
    {
        for(unsigned int c = 0; c < cols; c++)
        {
            if(table[r][c]->getHeight() > max_height[r]) max_height[r] = table[r][c]->getHeight();
            if(table[r][c]->getWidth() > max_width[c]) max_width[c] = table[r][c]->getWidth();
        }
    }
}

ostringstream&	operator<<	(ostringstream &oss, CTable& table)
{
    table.SetMaxWidthMaxHeight();
    oss << '+';
    for(auto it = table.max_width.begin(); it != table.max_width.end(); it++)
    {
        for(int i = 0; i < (*it); i++) oss << '-';
        oss << '+';
    }
    oss << '\n';
    for(int r = 0; r < (int)table.rows; r++)
    {
        for(int h = 0; h < table.max_height[r]; h++)
        {
            for(int c = 0; c < (int)table.cols; c++)
            {
                oss << '|';
                table.table[r][c]->output(oss, h, table.max_width[c], table.max_height[r]);
            }
            oss << "|\n";
        }
        oss << '+';
        for(auto it = table.max_width.begin(); it != table.max_width.end(); it++)
        {
            for(int i = 0; i < (*it); i++) oss << '-';
            oss << '+';
        }
        oss << '\n';
    }
    return oss;
}

CTable& CTable::operator= (const CTable& x)
{
    for (size_t r = 0; r < this->rows; r++)
    {
        for (size_t c = 0; c < this->cols; c++)
        {
            if(this->table[r][c]) delete this->table[r][c];
        }
        this->table[r].clear();
    }
    this->table.clear();
    this->rows = x.rows;
    this->cols = x.cols;
    this->max_width = x.max_width;
    this->max_height = x.max_height;
    for(auto it1 = x.table.begin(); it1 != x.table.end(); it1++)
    {
        vector<CCell*> push;
        for(auto it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
        {
            push.push_back((*it2)->clone());
        }
        this->table.push_back(push);
    }
    return *this;
}



#ifndef __PROGTEST__
int main(void)
{
    
    return 0;
}
#endif /* __PROGTEST__ */

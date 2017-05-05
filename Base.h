#include "string"
#include "iostream"

class Printable	
{
public:
	Printable() {};
	
	std::string GetInfo() const { 
			return _info;
	}

	friend std::ostream & operator << ( std::ostream & out, const Printable & printable ) {
		out << printable._info;
		return out;
	}

protected:
	std::string _info;
};

class Shape : virtual public Printable
{
public:
	Shape() {
		_count++;
	}

	Shape( std::string info ) {
		_count++;
	};

	Shape( const Shape& shape)
	{
		_info = shape._info;
		_count++;
	}

	static int GetCount() {
		return _count;
	}

	virtual void PrintInfo(std::ostream &out) {out << "Shape";}

	virtual ~Shape() {
	_count--;
	} 

protected:
	static int _count;
};

class Named : virtual public Printable
{
public:

	Named( std::string const name ) 
	{
		this->_name = name;
	};
	
	std::string const & GetName() {
		return _name;
	}
	
protected:
	std::string _name;
};
	int Shape::_count = 0;

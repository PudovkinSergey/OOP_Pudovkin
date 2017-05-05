#include "Base.h"
#include"sstream"
#include "Container.h"
#include <vector>
// type to string
template <typename T>		
std::string ToString( T val )
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

class Point : public Shape, public Named
{
public:
	Point() :Shape(), Named("") {};

	Point( std::string const name, double x, double y ) : Shape(), Named( name ) {
		_x = x;
		_y = y;
		_info = "Point named " + this->GetName() + " with coordinates:(" + ToString( _x ) + "," + ToString( _y ) + ")\n";
	};

	Point( const Point & point ) : Shape(), Named( point._name ) {
		_x = point._x;
		_y = point._y;
		_info = "Point named " + point._name + " with coordinates:(" + ToString( _x ) + "," + ToString( _y ) + ")\n";
	};

	double GetX() { return _x; };

	double GetY() { return _y; };

	static double Distance( const Point & x, const Point & y ) {
		return pow( ( pow( x._x - y._x, 2 ) + pow( ( x._y - y._y ), 2 ) ), 0.5 );
	}

	~Point() {};

private:
	double _x;
	double _y;
};

class Circle : public Shape, public Named {
public:
	Circle() :Shape(), Named( "" ) {};

	Circle( std::string const name, Point point, double r ):Shape(),Named( name ) {
		_center = new Point( point );
		_radius = abs( r );
		_info="Circle named " + this->GetName() + "with center:" + point.GetInfo() + "radius: "+ ToString(_radius)+ " \nand area = "+ ToString( _radius*_radius*3.1415 )+"\n";
	}

	~Circle() {
		delete _center;
	}

private:
	Point* _center;
	double _radius;
};

class Rectangle : public Shape, Named {
public:
	Rectangle() :Shape(), Named( "" ) {};

	Rectangle( std::string const name, std::string type, Point x1, Point x2, Point x3, Point x4 ) :Shape(  ), Named( name ) {
		_x1 = new Point( x1 );
		_x2 = new Point( x2 );
		_x3 = new Point( x3 );
		_x4 = new Point( x4 );
		_info = "It is " + type + " named " + this->GetName() + "with points: \n" + _x1->GetInfo() + _x2->GetInfo() + _x3->GetInfo() + _x4->GetInfo() + "and area: " + ToString(this->AreaOfRect())+"\n"  ;
	}

	~Rectangle(){
		delete _x1;
		delete _x2;
		delete _x3;
		delete _x4;
	}

	virtual double  AreaOfRect() {
		return Point::Distance( *_x1, *_x2 ) * Point::Distance( *_x2, *_x3 );
	}

protected:
	Point* _x1;
	Point* _x2;
	Point* _x3;
	Point* _x4;
};

class Square : public Rectangle {
public:
	Square() : Rectangle() {};

	Square( std::string const name, Point x1, Point x2, Point x3, Point x4 ) : Rectangle( name, "Square", x1, x2, x3, x4 ) { if ( round( abs( x1.GetX() - x3.GetX() )*10000 )/10000 != round( abs(x1.GetY() - x3.GetY() ) * 10000) / 10000) throw "Can't create square, points are wrong!"; };
	
};

class Rect : public Rectangle {
public:
	Rect() : Rectangle() {};

	Rect( std::string const name, Point x1, Point x2 ) {
		if ( x1.GetX() == x2.GetX() || x1.GetY() == x2.GetY() ) throw "Can't create Rect, points are similar";
		_x1 = new Point( x1 );
		_x2 = new Point( _x1->GetName(), _x1->GetX(), x2.GetY() );
		_x3 = new Point( x2 );
		_x4 = new Point( _x2->GetName(), _x2->GetX(), _x1->GetY() );
		_info = "It is Rect named " + name + "with points: \n" + _x1->GetInfo() + _x2->GetInfo() + _x3->GetInfo() + _x4->GetInfo() + "and area: " + ToString(this->AreaOfRect())+"\n";
	}
};

class Polyline : public Shape, public Named {
public:
	Polyline() : Shape(), Named("") {};

	Polyline( std::string name ) : Shape(), Named( name ) {};
	
	void AddPoint( const Point &point ) {
		if ( _points.GetCount() >= 1 ) {
			_length += Point::Distance( point,_points.GetTail() );
		}
		_info = "It is Polyline named " + this->_name + " with length: " + ToString( _length )+"\n";
		_points.InsTail( point );
	};

	double GetLength() {
		return _length;
	}

	~Polyline() { }
	
private:
	Container< Point > _points ;
	double _length = 0;
};

class Polygon : public Shape, public Named {
public:
	Polygon() : Shape(), Named( "" ) {};
	
	Polygon( std::string name ):Shape(),Named( name ) {};
	
	void AddPoint( const Point & point ) {
		if ( _points.GetCount() >= 1 ) {
			_length += point.Distance( point,_points.GetTail() );
			_points.DelHead();
			_points.InsHead( point );
			_points.InsTail( point );
		}
		else {
			_points.InsTail( point );	
		}
		_info = "It is Polygon named " + this->_name + " with length: " + ToString( _length ) + "\n";
	}

	double GetLength() {
		return _length;
	}
private:
	Container< Point > _points;
	double _length = 0;

};
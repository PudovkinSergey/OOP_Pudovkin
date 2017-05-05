#include <iterator>	

template< class T > class Container {
	struct Node {
		Node(T elem) {
			_element = elem;
			next = NULL;
		}
		T _element;
		Node * next;
	};
public:

 	Container() {
		_head = 0;
		_tail = 0;
		_count = 0;
	}

	virtual ~Container() {
		while (!IsEmpty()) this->DelHead();
	}

	void SetToFirst()
	{
		if (_head == NULL) throw "Can't set to first, container is empty!";
		_iterpointer = _head;
	}

	const T* GetAndMove()
	{
		if ( _iterpointer->next != NULL )
		{
			_iterpointer = _iterpointer->next;
			return &_iterpointer->content;
		}
		else return NULL;
	}
	
	void InsHead( const T & element ) {
			if ( _head == 0 ) {
			Node * temp = new Node( element );
			_head = temp;
			_tail = temp;
		}
		else {
			Node * temp = new Node( element );
			temp->next = _head;
			_head = temp;
		}
		_count++;
	}

	void InsTail( const T & element ) {
		if ((_head == 0)) {
			Node * temp = new Node( element );
			_head = temp;
			_tail = temp;
		}
		else {
			Node * temp = new Node( element );
			_tail->next = temp;
			_tail = temp;
		}
		_count++;
	}

	void DelHead() {
		if ( _head == 0 ) throw "Can't delete head, container is empty";
		if ( _head == _tail ) {
			Node *temp = _head;
			_head = _head->next;
			delete temp;
			_head = 0;
			_tail = 0;
			_count--;
		}
		else {
			Node * temp = _head;
			_head = _head->next;
			delete temp;
			_count--;
		}
	}
	void DelTail() {
		if ( _head == 0 ) throw "Can't delete tail, container is empty";
		if ( _head == _tail ) {
			delete _head;
			_head = 0;
			_tail = 0;
			_count--;
		}
		else {
			Node * temp = _head;
			while ( temp->next != _tail ) {
				temp = temp->next;
			}
			delete _tail;
			_tail = temp;
			_tail->next = 0;
			_count--;
		}
	}

	const T & GetHead() {
		if ( _head == 0 ) throw "Can't get head, container is empty";
		return _head->_element;
	}

	const T & GetTail() {
		if ( _head == 0 ) throw "Can't get tail, container is empty";
		return _tail->_element;
	}

	int GetCount() {
		return _count;
	}

	bool IsEmpty() {
		if ( _count == 0 ) return true;
		else return false;
	}

	void Clear() {
		while ( !IsEmpty() ) {
			DelHead();
		}
	}
	
	void PrintContainer() {
		if ( _head == NULL ) throw "Can't print, container is empty!";
		Node * temp = _head;
		while (temp != 0) {
			std::cout << temp->_element << std::endl;
			temp = temp->next;
		}

	}

private:
	
	int _count = 0;
	Node * _head ;
	Node *_tail ;
	Node *_iterpointer ;
};


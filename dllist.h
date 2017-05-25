#ifndef DLLIST_H_
#define DLLIST_H_
#include <iterator>

template <class T>
class DList
{

	struct Node{

       Node (const T& x, Node* y=0): m_data (x), m_prev (y), m_next (y){};//contructors for the pointers.
	   T m_data;//value within the node.
	   Node *m_prev;//previous pointer making it doubly-linked
	   Node *m_next;//next pointer

	};

	  Node* m_header; //creation of the header node

public:


	  DList(){

		  m_header=new Node(T());//Header contructor
		  m_header->m_prev=m_header;//Makes the header point to itself.
		  m_header->m_next=m_header;
	  }


	class iterator
    {
			Node* m_rep;

	public:

		friend class DList;

		inline iterator(Node* x=0):m_rep(x){}
		inline iterator(const iterator& x):m_rep(x.m_rep) {}
		inline iterator& operator=(const iterator& x)
		{
			m_rep=x.m_rep; return *this;
		}
		inline iterator& operator++()
		{
			m_rep = m_rep->m_next; return *this;
		}
		inline iterator operator++(int)
		{
			iterator tmp(*this); m_rep = m_rep->m_next; return tmp;
		}
		inline T& operator*() const { return m_rep->m_data; }
		inline Node* operator->() const { return m_rep; }
		inline bool operator==(const iterator& x) const
		{
			return m_rep == x.m_rep;
		}
		inline bool operator!=(const iterator& x) const
		{
			return m_rep != x.m_rep;
		}

	};


		~DList() { clear(); }
		void clear() { while (!empty()) pop_front(); }

		inline void push_front (const T&x)
		{
			Node* tmp = new Node(x);

			tmp->m_next=m_header->m_next; //temp points to whatever header pointed to.

			m_header->m_next=tmp;//Header points to temp.

			tmp->m_prev=m_header;//temp points to head.

			tmp->m_next->m_prev=tmp;//whatever header pointed to now points to header.

		}
		inline void pop_front()
		{

			if (m_header->m_next){

				Node*head=m_header->m_next;
				Node*newhead=head->m_next;

				delete m_header->m_next;//deletes headers next;

				m_header->m_next=newhead;//whatever was after the header is now pointing to.

				newhead->m_prev=m_header;//whatever was after points to header.

			}


		}
		inline bool empty() { return m_header->m_next==m_header; }

		inline T& front() { return *begin(); }
		inline const T& front() const { return *begin(iterator()); }

		inline iterator begin() { return iterator(m_header->m_next); }//uses the headers pointers to find begin and end.
		inline iterator end() { return iterator(m_header->m_prev); }

		// insert y before x. Intended to parallel vector operation
		void insert (iterator& x, const T& y) {

			Node *tmp = new Node(y, x.m_rep);		// new node's next will be x's node

			if (x.m_rep==m_header->m_next) {

				tmp->m_next=m_header->m_next; //If its the first value executes push_front.

				m_header->m_next=tmp;

				tmp->m_prev=m_header;

				tmp->m_next->m_prev=tmp;

			}
			else {
				Node *p = m_header->m_next;

				while (p && p->m_next != x.m_rep) p = p->m_next;
					  if (!p) throw std::exception();
						  Node* pos = p->m_next;//saves the position where the value is going to be.

						  pos = tmp; //assigns tmp to the position.

						  tmp->m_next=pos->m_next;//tmp points to what pos pointed to.
						  pos->m_next->m_prev=tmp;//what was after pos points to tmp now.

						  tmp->m_prev=pos;//tmps previous now points to pos.
						  pos->m_next=tmp;//pos next now points to tmp.



			}
		}

		// push back. Intended to parallel vector operation
		void push_back (const T& y) {

			Node *nd = new Node(y, NULL);

			if (!m_header->m_next) m_header->m_next = nd;//if list is empty.
			else {
				Node *p = m_header->m_next;
				while (p->m_next) p = p->m_next;//loops through the list.

				p->m_next = nd;//inserts the node at the end of the list makes second to last node point to last node.
				nd->m_prev=p;//the last node now points to the second to last node.
				nd->m_next=m_header;//the last node points to header.
				m_header->m_prev=nd;//header also points to last node.

			}
		}

};





#endif /* DLLIST_H_ */

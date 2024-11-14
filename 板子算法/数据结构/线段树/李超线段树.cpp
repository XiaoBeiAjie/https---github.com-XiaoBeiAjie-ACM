#include <iostream>
#include <cstring>
#include <queue>
#include <map>
#include <cstdio>
#include <unordered_map>
#include <deque>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include <bitset>
#include <limits.h>
#define x first
#define y second

using namespace std;
typedef  long long LL;
typedef long long ll  ; 
typedef pair<int,int> PII;
typedef pair<int,LL> PIL;
typedef pair<int ,PII> PIII ;
typedef pair<LL , LL> PLL ; 
typedef pair<LL ,int > PLI ;
typedef pair<int,char > PIC ; 
typedef unsigned long long ULL ;

const int N = 1e5+10,M = 6e5+10  ;
const LL mod = 1e9+7, INF = 1e12+10;
const double eps = 1e-7 ;



const ULL  P=  131 ;


int n , m   , k ;

template< class T > 
struct line{
	T k , b ;
	line( T _k = 0 , T _b = 0 ): k( _k)  ,b( _b ) { }
	T operator( )( T x ) {  return k*x + b ; }  
};

template<typename T>
class segTree{
	struct node{
		int l ,r , id ;
 	};
	public :
		int size ;
		vector<node> tr;
		vector< line<T> >  f;
		vector<T>  x ; 
	segTree( int _size ) :size(_size) , tr( (_size+1)*4   ) ,f( N ),x( _size + 1 )  {  	} 
	
	void build( int x ,int l ,int r  ) {
		tr[x] = { l , r , 0  } ;
		if( l == r )return ;
		int mid = l +r >> 1 ;
		build( x << 1  , l , mid ) ;build( x <<1 | 1 , mid + 1, r ) ;
	}
	
	void insert( int pos , T k, T b  ,int l , int r   ) {
		f[pos] = { k , b} ;
		update( 1 , l , r ,pos )  ;
	}
	//  f(u ) == f( v ) ?
	bool equal( T a , T b) {
		if( fabs( a -b ) < eps ) return true ;
		return false ;
	}
	//  u > v ?  
	bool judge( int u , int v , int  x  ) {
		if( !u ) return false ;
		if( !v ) return true ;  
		T  fx = (f[u])( x )  ,fy = (f[v])(x) ;
		return equal( fx ,fy) ? u < v : fx > fy ; 
	}
	
	void update( int u , int l , int r , int pos ) {
		if( tr[u].r < l   || tr[u].l > r ) return ;
		int mid = tr[u].l  + tr[u].r >> 1  ;
		if( l <= tr[u].l && r >= tr[u].r ) {
			
			if( judge(  tr[u].id , pos , tr[u].l ) && judge( tr[u].id , pos , tr[u].r)  ) return ;
			if( judge(  pos  , tr[u].id, tr[u].l ) && judge( pos  ,tr[u].id , tr[u].r)  )  {
				tr[u].id = pos ; return ; 
			}
			if( judge(  pos , tr[u].id , mid )) swap( tr[u].id, pos  ) ;
			if( judge(  pos , tr[u].id , tr[u].l  ) ) update( u << 1  , l , r , pos ) ;
			if( judge(  pos , tr[u].id , tr[u].r  ) ) update( u << 1 | 1 , l , r , pos ) ;
			return ;
		}
		if( l <= mid ) update( u << 1 ,  l , r , pos ) ;
		if( r > mid  ) update( u << 1 | 1, l ,r , pos) ;
	}
	
	void changex( int pos , T _x) { x[pos] = _x  ; } 
	
	int query( int u , int pos ) {
		if( tr[u].l == pos && tr[u].r == pos) return tr[u].id;
		int mid = tr[u].l + tr[u].r  >> 1 ,res = 0; 
		if( pos <= mid )  res  = query( u << 1 ,  pos ) ;
		if( pos >  mid )  res  = query( u << 1 | 1, pos ) ;
		if( judge(  tr[u].id , res , pos  ) )  res = tr[u].id;
		return res ;
	}
	
	
};

const int maxn = 39989 ; 
	

void solve() { 
	cin >> n ;
	segTree< double > sg( maxn ) ;   
	sg.build( 1 , 1 ,  maxn)  ;
	int lst = 0 ,cnt = 0; 
	while( n --) {
		int op ;  cin >> op ;
		if( op == 0 ) {
			int k ; cin >> k ;
			k = ( k + lst -1 ) %maxn  + 1 ;
			lst =sg.query( 1 ,  k) ;
			cout << lst <<'\n' ;
		}else {
			int x0 ,x1 , y0 , y1 ;
			cin >> x0 >> y0 >> x1 >> y1 ;
			x0  = ( x0 + lst -1  +  maxn) %maxn  + 1 ;
			x1  = ( x1 + lst -1  +  maxn) %maxn  + 1 ;
			y0  = ( y0 + lst -1  + 1000000000)%1000000000 + 1 ;
			y1  = ( y1 + lst -1  + 1000000000)%1000000000 + 1 ;
			if( x0 > x1 ) swap( x0 ,x1) ,swap( y0, y1 ) ;
			double k = 0 , b = max( y0 , y1 ) ;
			if( x0 != x1) {
				k = 1.0*( y0-y1)/(x0 - x1)  ,b =  y0 - k*x0 ; 
			}
			sg.insert( ++cnt , k , b , x0 , x1  ) ;
		}
	}
}	

int main(){ 	
	ios::sync_with_stdio(true);
	cin.tie( 0 ) ;
	int T;T  =1; 
	while(T-- ){	
		solve() ;  
   	}        
 	return  0 ;
}

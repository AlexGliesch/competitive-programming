//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <cstring>
//#include <iomanip>
//using namespace std;
//
//double m[1000][1000];
//int n;
//
//
//struct node{
//	node(){
//		p1=p2=f=id=-1;
//	}
//	int id;
//	bool concrete(){ return id <= n; }
//	int p1, p2, f;
//};
//
//vector<node> nodes;
//vector<vector<double> > dp;
//
//double prob(int na, int nb){
//	node& a=nodes[na], &b=nodes[nb];
//	// cout << "prob("<<na<<","<<nb<<")\n";
//
//	if (dp[na][nb]!= -1){
//		// cout<<"p("<<na<<","<<nb<<") ="<<dp[na][nb]<<endl;
//		return dp[na][nb];
//	} 
//	// else if (dp[nb][na] != -1){
//	// 	dp[na][nb] = 1-dp[nb][na];
//	// 	// cout<<"p("<<na<<","<<nb<<") ="<<dp[na][nb]<<endl;
//	// 	return dp[na][nb];
//	// }
//
//	if (a.concrete() and b.concrete())
//		dp[na][nb] = m[a.id][b.id];
//	else if (a.concrete() and not b.concrete()){
//		dp[na][nb] = prob(na, b.p1) * prob(b.p1, b.p2)
//			+ prob(na, b.p2)*prob(b.p2, b.p1);			
//	} 
//	else if (not a.concrete() and b.concrete()){
//		dp[na][nb]=prob(a.p1,a.p2)*prob(a.p1,nb) 
//			+ prob(a.p2,a.p1)*prob(a.p2,nb);
//	}
//	else {
//		dp[na][nb] =
//		  prob(a.p1,a.p2)*prob(a.p1,nb)		
//		+ prob(a.p2,a.p1)*prob(a.p2,nb);
//		//   prob(a.p1,a.p2)*prob(b.p1,b.p2)*prob(a.p1,b.p1)
//		// + prob(a.p1,a.p2)*prob(b.p2,b.p1)*prob(a.p1,b.p2)
//		// + prob(a.p2,a.p1)*prob(b.p1,b.p2)*prob(a.p2,b.p1)
//		// + prob(a.p2,a.p1)*prob(b.p2,b.p1)*prob(a.p2,b.p2);
//	}
//	// cout<<"p("<<na<<","<<nb<<") ="<<dp[na][nb]<<endl;
//	return dp[na][nb];
//}
//
//int main(){
//	while(cin>>n, n){
//		// cout<<"n="<<n <<endl;
//		for (int i=1;i<=n;++i){
//			for (int j=1;j<=n;++j){
//				cin>>m[i][j];
//			}
//		}
//		nodes.clear(); nodes.resize(2*n-1+100);
//		
//		for (int i=1;i<=n; ++i){
//			nodes[i].id=i;
//		}
//
//		for (int i=n+1; i<= 2*n-1;++i){
//			int a,b;cin>>a>>b;
//
//			node& h = nodes[i];
//			h.id = i;
//			h.p1=a;
//			h.p2=b;
//			nodes[a].f = h.id;
//			nodes[b].f = h.id;
//		}
//
//		dp.assign(1000, vector<double>(1000,-1));
//		int i=1;
//		double ans=1;
//		while(true){
//			// cout<<"i = " << i<<endl;
//			if (nodes[i].f==-1) {				
//				break;
//			}
//			
//			if (nodes[nodes[i].f].p1 == i) {
//				// cout<<"ans *= p("<<1 <<", " << nodes[nodes[i].f].p2<<")\n"; 
//
//				// cout << "p("<<1 <<", " << nodes[nodes[i].f].p2<<") = "
//					// << prob(1, nodes[nodes[i].f].p2) << endl;
//
//				ans*=prob(1, nodes[nodes[i].f].p2);
//			} else {
//				// cout<<"ans *= p("<<1 <<", " << nodes[nodes[i].f].p1<<")\n";
//
//				// cout << "p("<<1 <<", " << nodes[nodes[i].f].p1<<") = "
//					// << prob(1, nodes[nodes[i].f].p1) << endl;
//
//				ans*=prob(1, nodes[nodes[i].f].p1);
//			}
//			i = nodes[i].f;
//		}
//		cout<<setprecision(6)<<fixed<<ans<<endl;
//	}
//}

#include<bits/stdc++.h>
using namespace std;

class SGTree{

	vector<pair<int,int>> seg;

	public:
	SGTree(int n){
		seg.resize(4*n+1);
	}

	void build(int ind,int low,int high,int arr[]){
		if(low == high){
			seg[ind] = {arr[low],-1e9};
			return;
		}
		int mid = (low+high)/2;
	    int left = ind*2+1;
	    int right = left+1;

		build(left,low,mid,arr);
		build(right,mid+1,high,arr);


    	vector<int> v = {seg[left].first, seg[left].second, seg[right].first, seg[right].second};

	    sort(v.begin(), v.end());

	    seg[ind].first=v[2];
	    seg[ind].second=v[3];

	}


	void update(int ind,int low,int high,int i,int val){
		if(low == high){
			seg[ind].first = val;
			return;
		}
		int mid = (low+high)/2;
	    int left = ind*2+1;
	    int right = left+1;

		if(i<=mid) update(left,low,mid,i,val);
		else update(right,mid+1,high,i,val);


    	vector<int> v = {seg[left].first, seg[left].second, seg[right].first, seg[right].second};

	    sort(v.begin(), v.end());

	    seg[ind].first=v[2];
	    seg[ind].second=v[3];

	}

	pair<int,int> query(int ind,int low,int high,int l,int r){

		//no overlap
		//l r low mid or low mid l r
		if(r < low || high < l) return {-1e9,-1e9};
		//complete overlap
		//l low high r
		if(low >= l && high <=r) return seg[ind];

		int mid = (low+high)/2;

		pair<int,int> left = query(2*ind+1,low,mid,l,r);
		pair<int,int> right = query(2*ind+2,mid+1,high,l,r);

		vector<int> v = {left.first, left.second,right.first, right.second};
	    sort(v.begin(), v.end());

		return seg[ind] = {v[2],v[3]};

	}


};

int main(){
	#ifndef ONLINE_JUDGE
		freopen("input1.txt","r",stdin);
		freopen("output1.txt","w",stdout);
	#endif

		int n;
		cin>>n;
		int arr[n];
		for(int i=0;i<n;i++) cin>>arr[i];

		SGTree st(n);
		st.build(0,0,n-1,arr);


		int q;
		cin>>q;
		while(q--){
			char c;
			int l,r;
			cin>>c>>l>>r;
			
			if(c == 'Q'){
				pair<int,int> ans = st.query(0,0,n-1,l,r);

				cout<<ans.first+ans.second<<endl;
			}
			else{
				st.update(0,0,n-1,l,r);
			}

		}

	return 0;
}

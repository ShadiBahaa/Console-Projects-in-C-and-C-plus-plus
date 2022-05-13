#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    const int x = n;
    char arr[x][x];
    int vis[x][x];
    memset(arr,'.',sizeof(arr));
    memset(vis,0,sizeof(vis));
    bool playerx = true;
    int winx = 0;
    int winy = 0;
    int cnt = 0;
    while (true){
        if (cnt== n*n){
            cout<<"tie"<<endl;
            return 0;
        }
        if (playerx){
            cout<<"Player x turn. Enter empty location (r,c): "<<endl;
            int r,c;
            cin>>r>>c;
            if (!vis[r][c] && r<n && c<n && r>=0 && c>=0){
                arr[r][c]='x';
                vis[r][c]=1;
                for (int i = 0; i<n;i ++){
                    for (int j = 0; j<n; j++){
                        cout<<arr[i][j]<<" ";
                }
                cout<<endl;
                }
                playerx = false;
                cnt++;
            }else {
                cout<<"Invalid input. Try again"<<endl;
                continue;
            }
        }else {
            cout<<"Player o turn. Enter empty location (r,c): "<<endl;
            int r,c;
            cin>>r>>c;
            if (!vis[r][c] && r<n && c<n && r>=0 && c>=0){
                arr[r][c]='o';
                vis[r][c]=1;
                for (int i = 0; i<n;i ++){
                    for (int j = 0; j<n; j++){
                        cout<<arr[i][j]<<" ";
                }
                cout<<endl;
                }
                playerx = true;
                cnt++;
            }else {
                cout<<"Invalid input. Try again"<<endl;
                continue;
            }
        }
        if (!playerx){
            for (int i = 0 ; i<n-1 ; i++){
                if (arr[i][i]==arr[i+1][i+1] && arr[i][i]=='x'){
                    winx++;
                }else {
                    break;
                }
            }
            if (winx == n-1){
                cout<<"Player x won"<<endl;
                return 0;
            }
            winx = 0;
            for (int i = 0 ; i<n-1 ; i++){
                if (arr[i][n-i-1]==arr[i+1][n-i-2] && arr[i][n-i-1]=='x'){
                    winx++;
                }else {
                    break;
                }
            }
            if (winx == n-1){
                cout<<"Player x won"<<endl;
                return 0;
            }
            winx = 0;
            for (int i = 0 ; i<n ; i++){
                    winx = 0;
                for (int j = 0; j<n-1; j++){
                    if (arr[i][j]==arr[i][j+1] && arr[i][j]=='x'){
                        winx++;
                    }
                    else {break;}
                }
                if (winx == n-1){
                    cout<<"Player x won"<<endl;
                    return 0;
                }
            }
            winx = 0;
            for (int i = 0 ; i<n ; i++){
                    winx = 0;
                for (int j = 0; j<n-1; j++){
                    if (arr[j][i]==arr[j+1][i] && arr[j][i]=='x'){
                        winx++;
                    }
                    else {break;}
                }
                if (winx == n-1){
                    cout<<"Player x won"<<endl;
                    return 0;
                }
            }
            winx = 0;
        }else {
            for (int i = 0 ; i<n-1 ; i++){
                if (arr[i][i]==arr[i+1][i+1] && arr[i][i]=='o'){
                    winy++;
                }else {
                    break;
                }
            }
            if (winy == n-1){
                cout<<"Player o won"<<endl;
                return 0;
            }
            winy = 0;
            for (int i = 0 ; i<n-1 ; i++){
                if (arr[i][n-i-1]==arr[i+1][n-i-2] && arr[i][n-i-1]=='o'){
                    winy++;
                }else {
                    break;
                }
            }
            if (winy == n-1){
                cout<<"Player o won"<<endl;
                return 0;
            }
            winy = 0;
            for (int i = 0 ; i<n ; i++){
                    winy = 0;
                for (int j = 0; j<n-1; j++){
                    if (arr[i][j]==arr[i][j+1] && arr[i][j]=='o'){
                        winy++;
                    }
                    else {break;}
                }
                if (winy == n-1){
                    cout<<"Player o won"<<endl;
                    return 0;
                }
            }
            winy = 0;
            for (int i = 0 ; i<n ; i++){
                    winy = 0;
                for (int j = 0; j<n-1; j++){
                    if (arr[j][i]==arr[j+1][i] && arr[j][i]=='x'){
                        winy++;
                    }
                    else {break;}
                }
                if (winy == n-1){
                    cout<<"Player o won"<<endl;
                    return 0;
                }
            }
            winy = 0;
        }
    }
}

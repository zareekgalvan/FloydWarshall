//
//  main.cpp
//  FloydWarshall
//
//  Created by Zareek Galvan on 10/25/15.
//  Copyright © 2015 Trisquel Labs. All rights reserved.
//

#include <iostream>
using namespace std;
#include <climits>
#include <stack>

int mat[10][10];
int matNext[10][10];

void inicializaMatriz()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            mat[i][j] = INT_MAX/4;
            matNext[i][j] = 0;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        mat[i][i] = 0;
        matNext[i][i] = i+1;
    }
}

void printMat(int n)
{
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printMatNext(int n)
{
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matNext[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void floyd(int n)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (mat[i][k] + mat[k][j] < mat[i][j])
                {
                    matNext[i][j] = k+1;
                    mat[i][j] = mat[i][k] + mat[k][j];
                    //printMatNext(n);
                }
            }
        }
    }
}

void displayRoute(int n1, int n2)
{
    stack<int> s;
    while (matNext[n1][n2] != 0)
    {
        s.push(matNext[n1][n2]);
        n2 = matNext[n1][n2] - 1;
    }
    while (!s.empty())
    {
        cout << "-" << s.top();
        s.pop();
    }
}

int main()
{
    inicializaMatriz();
    
    int nodes, arcs;
    cin >> nodes >> arcs;
    for (int i = 0; i < arcs; i++)
    {
        int n1, n2, val;
        cin >> n1 >> n2 >> val;
        mat[n1-1][n2-1] = val;
        mat[n2-1][n1-1] = val;
    }
    
    floyd(nodes);
    printMat(nodes);
    printMatNext(nodes);
    
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int q1, q2;
        cin >> q1 >> q2;
        cout << mat[q1-1][q2-1] << " " << q1;
        displayRoute(q1-1, q2-1);
        cout << "-" << q2 << endl;
    }
    
}
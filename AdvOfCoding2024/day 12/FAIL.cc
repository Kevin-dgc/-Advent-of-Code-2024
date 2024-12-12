
int findPerimeterFAIL(char cur, pair<int, int> pos, vector<vector<char>> grid, map<pair<int, int>,bool>& visited){
    if(grid[pos.first][pos.second] != cur){
        return 1;
    }
    visited[pos] = true;

    int sum = 0;
    pair<int, int> up = make_pair(pos.first - 1, pos.second);
    pair<int, int> down = make_pair(pos.first + 1, pos.second);
    pair<int, int> left = make_pair(pos.first, pos.second - 1);
    pair<int, int> right = make_pair(pos.first, pos.second + 1);

    if(visited[up] == false){
        if(up.first >= 0 && up.first < grid.size() && up.second >= 0 && up.second < grid[0].size()){ 
            sum += findPerimeter(cur, up, grid, visited);
        }
        else{
            sum += 1;
        }
    }
    if(visited[down] == false){
        if(down.first >= 0 && down.first < grid.size() && down.second >= 0 && down.second < grid[0].size()){ 
            sum += findPerimeter(cur, down, grid, visited);
        }
        else{
            sum += 1;
        }
    }
    if(visited[left] == false){
        if(left.first >= 0 && left.first < grid.size() && left.second >= 0 && left.second < grid[0].size()){ 
            sum += findPerimeter(cur, left, grid, visited);
        }
        else{
            sum += 1;
        }
    }
    if(visited[right] == false){
        if(right.first >= 0 && right.first < grid.size() && right.second >= 0 && right.second < grid[0].size()){ 
            sum += findPerimeter(cur, right, grid, visited);
        }
        else{
            sum += 1;
        }
    }

    return sum;
}

int advFAIL(vector<vector<char>> grid){
    int totalCost = 0;
    map<pair<int, int>,bool> visited;
    

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            pair<int, int> pos = make_pair(i, j);
            if(visited[pos] == false){ // if it's not visited and not a space
                visited[pos] = true;
                map<pair<int, int>,bool> perimeterVisited;
                int perimeter = findPerimeter2(grid[i][j], pos, grid, perimeterVisited);
                int area = findArea(grid[i][j], pos, grid, visited);

                int cost = (area * perimeter);
                cout << "A region of " << grid[i][j] << " at x:" << j << " at y: " << i << " plants with price " << area << " * " << perimeter << " = " << cost << endl;
                totalCost += cost;
                

                //prints out current grid
                // for(int row = 0; row < grid.size(); row++){
                //     for(int col = 0; col < grid[row].size(); col++){
                //         pair<int,int> posC = make_pair(row, col);
                //         if(visited[posC] == true){
                //             char c = grid[row][col];
                //             if(c == grid[i][j]){
                //                 cout << c;
                //             }
                //             else{
                //                 cout << (char)tolower(c);
                //             }
                //         }
                //         else{
                //             cout << " ";
                //         }
                //     }
                //     cout << endl;
                // }
                // cout << endl << endl;
            } 
        }
    }
    

    return totalCost;
}

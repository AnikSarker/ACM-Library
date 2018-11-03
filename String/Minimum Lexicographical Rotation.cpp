int minimumExpression(string s) {
	s = s + s; 
	int i = 0, j = 1, k = 0, len = s.size(); 
	while(i + k < len && j + k < len) {
		if(s[i + k] == s[j + k]) k++;
		else if(s[i + k] < s[j + k]) { j = max(j + k + 1, i + 1); k = 0; }
		else { i = max(i + k + 1, j + 1); k = 0; }
	}
	return min(i, j);
}

class Solution {
public:
  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    int i = 0;
    vector<string> ans;
    while (i < words.size()) {
      int tw = 0; // (total width with mandatory spaces)
      int b = i;
      string line;
      while (i < words.size() && tw + words[i].size() + (tw > 0) <= maxWidth) {
        tw += words[i].size() + (tw > 0);
        ++i;
      }

      if (i == words.size()) { // last line
        for (int j = b; j < i; ++j) {
          if (j != b) line += ' ';
          line += words[j];
        }
        line += string(maxWidth - line.size(), ' ');
        assert(line.size() == maxWidth);
        ans.push_back(line);
        continue;
      } else {
        // select words b through i
        int numSlots = (i - b - 1);
        if (numSlots == 0) { // line with just one word
          assert(i == b + 1);
          line = words[b];
          line += string(maxWidth - line.size(), ' ');
        } else {
          int ww = tw - numSlots; // (words width without mandatory spaces)
          int spacesToAdd = maxWidth - ww;
          int minSpacesPerSlot = spacesToAdd / numSlots;
          assert(minSpacesPerSlot >= 1);
          int extraSpaces =
              spacesToAdd %
              numSlots; // slots [0, extraSpaces-1] receive one extra space

          line += words[b];
          int j = 1;

          while (b + j < i) {
            if (j - 1 <= extraSpaces - 1) line += ' ';
            line += string(minSpacesPerSlot, ' ');
            line += words[b + j];
            ++j;
          }
        }
      }
      assert(i != words.size() || line.back() != ' ');
      assert(line.size() == maxWidth);
      ans.push_back(line);
    }
    return ans;
  }
};
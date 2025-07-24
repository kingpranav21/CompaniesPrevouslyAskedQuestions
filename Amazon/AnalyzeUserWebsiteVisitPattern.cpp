//AnalyzeUserWebsiteVisitPattern.cpp

// In this problem, we are given the browsing history of multiple users stored in three arrays : 
// username, timestamp, and website.Each index i in these arrays represents a single browsing event, 
// where username[i] is the user who visited website[i] at time timestamp[i].The goal is to find a 
// sequence of three websites, which we will refer to as a "pattern," that is most popular among the 
// users.A pattern here means any three websites visited in a specific order, not necessarily different.
// The popularity or "score" of a pattern is determined by counting how many unique users visited the 
// websites in the same order as the pattern.The task is to return the pattern with the highest score, 
// and in case of a tie, return the lexicographically smallest pattern.

// Find the 3-sequence visited by the largest number of users. If there is more than one solution, return the lexicographically smallest such 3-sequence.

 

// Example 1:

// Input: username = ["joe","joe","joe","james","james","james","james","mary","mary","mary"], timestamp = [1,2,3,4,5,6,7,8,9,10], website = ["home","about","career","home","cart","maps","home","home","about","career"]
// Output: ["home","about","career"]
// Explanation: 
// The tuples in this example are:
// ["joe", 1, "home"]
// ["joe", 2, "about"]
// ["joe", 3, "career"]
// ["james", 4, "home"]
// ["james", 5, "cart"]
// ["james", 6, "maps"]
// ["james", 7, "home"]
// ["mary", 8, "home"]
// ["mary", 9, "about"]
// ["mary", 10, "career"]
// The 3-sequence ("home", "about", "career") was visited at least once by 2 users.
// The 3-sequence ("home", "cart", "maps") was visited at least once by 1 user.
// The 3-sequence ("home", "cart", "home") was visited at least once by 1 user.
// The 3-sequence ("home", "maps", "home") was visited at least once by 1 user.
// The 3-sequence ("cart", "maps", "home") was visited at least once by 1 user.
 

// Note:

// 3 <= N = username.length = timestamp.length = website.length <= 50
// 1 <= username[i].length <= 10
// 0 <= timestamp[i] <= 10^9
// 1 <= website[i].length <= 10
// Both username[i] and website[i] contain only lowercase characters.
// It is guaranteed that there is at least one user who visited at least 3 websites.
// No user visits two websites at the same time.

//no of usernmaes->n
//no of unique users->u
//no of websites -> m
//no of patterns
// TC-> O(n log m + u × m³ + P)
// SC-> O(n+P)

#include <bits/stdc++.h>
using namespace std;

vector<string> findMostVisitedPattern(vector<string> usernames, vector<int> timestamps, vector<string> websites)
{
    vector<string> res;
    // Step-1 creating an unordered map for user to map of time and website
    unordered_map<string, map<int, string>> userTotimestamp_to_websiteMap;
    for (int i = 0; i < usernames.size(); i++)
    {
        userTotimestamp_to_websiteMap[usernames[i]][timestamps[i]] = websites[i];
    }
    // joe -> {1->home}

    // Step-2 storing patterns as string(key) with their count(value)
    map<string, int> patternCount;
    for (auto &it : userTotimestamp_to_websiteMap)
    {
        // first take out websites to form a string
        vector<string> websites;
        for (auto &[timestamp, website] : it.second)
        {
            websites.push_back(website);
        }

        // now there will be multiple website patterns same but we need that
        // side static and count on the right side that will be updated
        unordered_set<string> websitePatternsKey;
        if (websites.size() < 3)
            continue; // no pattern skip

        for (int i = 0; i < websites.size() - 2; i++)
        {
            for (int j = i + 1; j < websites.size() - 1; j++)
            {
                for (int k = j + 1; k < websites.size(); k++)
                {
                    string pattern = websites[i] + '$' + websites[j] + '$' + websites[k];
                    websitePatternsKey.insert(pattern);
                }
            }
        }

        // now we got home$about$cart

        for (auto &pattern : websitePatternsKey)
        {
            patternCount[pattern]++;
        }
    }

    // Step-3 finding the pattern that is lexographically smaller or one with the highest count
    string mostFreqPattern;
    int maxCount = 0;
    for (auto &[pattern, count] : patternCount)
    {
        if (count > maxCount || (count == maxCount && pattern < mostFreqPattern))
        {
            mostFreqPattern = pattern;
            maxCount = count;
        }
    }
    cout << "mostFreqPattern : " << mostFreqPattern << endl;
    // Step-4 split the pattern key and put in the result
    string word;
    for (char ch : mostFreqPattern)
    {
        if (ch == '$')
        {
            res.push_back(word);
            word.clear();
        }
        else
            word += ch;
    }
    // last word after $
    res.push_back(word);
    return res;
}
int main()
{
    vector<int> timestamps = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<string> usernames = {"joe", "joe", "joe", "james", "james", "james", "james", "mary", "mary", "mary"};
    vector<string> websites = {"home", "about", "career", "home", "cart", "maps", "home", "home", "about", "career"};

    vector<string> res = findMostVisitedPattern(usernames, timestamps, websites);
    for (string site : res)
    {
        cout << site << " ";
    }
    cout << endl;
    return 0;
}

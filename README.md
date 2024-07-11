# **tuityping**
This is a TUI application for Typing Tests. It supports a zen mode that just lets you free type into a TUI screen, not much else. There is a words mode that collects 10 words from a pool of over 1000 of the most common words using a Reservoir Sample. If you want to run 15 or even 20 words feel free to do so, however output may be varying and support for different modes should come in the future. As of now this project is quite small and I simply wanted to have core functionality supported with a decent amount of code written. Please note that anything can break at any moment and there is no guarantee that this project will be actively maintained. 
# **How Calculations Work**
This application follows the tradition of MonkeyType in the sense that it takes the amount of characters you inputted and treat that as a more accurate assessment of your WPM rather than the 10 words given divided by time. This is to reduce things like larger words effecting your pool. What occurs is we take the number of character inputs and divide by 4.7 (Average length of word). Then we do the standard calculation and output it. Zen mode is the exact same, and it allows for a more accurate assessment of your test.
# **Future Plans**
As of now I simply want to support LocalLeaderBoards. This should be coming soon, but if not feel free to add it, it shouldn't be that bad. I also acknowledge that a lot of the code written could have been condensed, and as I went deeper in the project I began to realize this and hopefully I can coherently revise some of the code, optimize it, and make it a little more readable. Currently the file is a little over 300 lines of code, but honestly I can see it being less than 250. Finally, I would like to add perhaps timed test support, but as of now I will not do that. However as I become more entranced with ncurses I think I will give it a shot. Finally I would love to be able to support quotes and other things like pulling from a database with a bunch of nice lines. That doesn't seem so hard considering it really is just rewriting the word() function and factoring out the initial part of the Reservoir for another process. A lot of this seems feesible but we should just wait and see. 
# How to Run the Application
```bash
git clone --depth 1 https://github.com/starless333/tuityping
cd tuityping/src/
make
```

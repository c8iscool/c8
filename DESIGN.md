Design

I found a homepage html template online for the homepage of my website, and I replaced my images and text. I really liked the carousel feature from bootstrap that I used for pset 8 homepage, and I continued to implement that for a variety of pages in this project.

There are two tables in the database for this website: users and footprints. The users table contains the user_id, username, and total (carbon emissions) and the footprints table has total meat eaten, total miles traveled, the emissions from meat and the emissions from traveling.
When the user inputs an entry into the form on "input new activity," it inserts the user's value in the form to the table. The main table that is used and interacted with is footprints, since it also is responsible for displaying the history. Since the row "date" is done by default, and each entry has its corresponding date, I grouped the entries by the date so that in the footprint.html that displays the table of carbon emissions, it will sort by day.

In the page scoreboard, since the user_id is basically useless and is based on the sequence in which users register for accounts, I have to include both the users and footprints table so that username can be displayed. So, in the SQL query in application.py, I select both username from users as well as SUM(Total) from footprints, and then order by descending. In the scoreboard.html file, as it iterates through the number of items, the first data entry is just i+1 since it will show 1 through the number of registered users and will increment within the for loop.

The page “What’s the Cost?” is essentially the same thing as quote; I converted the user input in the form to a string for activity and set the cost and unit globally to 0. Then, if the activity matches one of the activities available from the input new activity, it will update those values and send it to another html which tells you how much carbon is emitted from a unit of that activity’s consumption.

I also researched how to make text appear/disappear from w3schools, and I implemented this in the ways to improve page so that alternatives could pop up with a button click. This way, I can keep the overall page as simple as possible and only provide extra information if the user wants to view it.

# Spookfish 
### A video Analysis and Statistics Tool.
### Motivation
When I started learning about the "Face Recognition" in [LearnOpencv course](https://courses.learnopencv.com/p/computer-vision-for-faces). I learnt that most of the effort in designing a very good model related to faces involves having excellent data set to feed it to any neural net. Any one who is new to this field like myself, follow a naive approach. i.e. Go to google.com and search the images by giving name of an actor/character and do a batch download using some  browser (chrome) plugins to download all the images. And try to sort and re-name each and every images meticulously to get some data. After putting hours of hard work, it feels really disheartening to see, all the hard work going in vein. When we observe poor performance of our data model against any neural net. In short, your model is only, as good as your dataset is. That is when, the idea of "spookfish" got seeded in my mind.


Of course there are n-number of freely available Image sets of celebrities available. But most of them are limited to Hollywood actors/actresses alone. What if I need to create my own dataset of actors of Bollywood or Sandlewood? What if I want have a dataset of all the CEO's of the famous companies? There is no easy way to get the desired quality images. Even the Hollywood actor/actress datasets are free to use to some extent, but not for commercial purposes. 

The goal of project "Spookfish" is to bridge that gap of acquiring effective data sets of any person with minimal efforts. Then, the next big question is, how can we get high quality images? There are couple of options.
- we can write some python scripts to scrape the images from internet.
- Buy the Images. (Of course I'm kidding.)

We can write python scripts using, [Beautiful soup](HTTPS://medium.freecodecamp.org/how-to-scrape-websites-with-python-and-beautifulsoup-5946935d93fe) to scrape large number of websites. But this approach has downside. Suppose, after a week if you run the same script again, nothing happens; why? Because lot of websites have changed their design and you are in big trouble. To get data as expected, you need to redo the scripts again. This involves lot of effort in maintaining the scripts itself. It is obvious that, We need a better solution.  A solution should be agnostic about the way websites are built. That is when the idea of using youtube/vimeo videos stands out. The UI,look and feel of these websites may change drastically, but the original content remains the same. Now that is the key point to remember.

Okay, we played some video and got some images, big deal. What is different about "Spookfish" then? "Spookfish" is not just Image capturing tool, it is a video analysis tool. Using "Spookfish" as a tool, you can capture the images, process the images the way you want it. Such as save images of specific dimension and aspect ratios. Get quality of Face data sets, with aligned face images. If you think about the face alignment option, it is a big deal. Because, the images which you gather from internet are not all aligned, and each image will be of its own dimension and size .Lot of manual work is involved to get the images processed. Once you have these basic criteria met, rest assured you are going to get better results in all the models which you intended to build. That is the idea behind this tool. We can also gather the details about the video being chosen for the analysis, and same video can be classified as movie/trailer/discussion/debate/documentary etc.. By extracting certain characteristics about the video. For example A TV interview of an actor about his or her upcoming movie. How to classify it as an interview? It may sound complex, but solution is pretty Simple,
- First check how many faces were identified in that video(say 5 mins). (Usually it will be two person, one anchor and other actor/actress.)
- Check how many close-up shots were there in that 5 min video.
- Check how many close-up shots of the actor are there in the video.
- Now lets co-relate the data. If there are two faces identified, and if there are more zoom shots of one person than the other, then, yes there is 90% chances that the video which was analyzed can be classified as "interview".

As you can see once you have the required details, it is just a matter of finding the if and else clauses to identify and classify the video appropriately.

Spookfish is that tool which gives you such an insight about the videos. Now you have the idea of how the video can be classified. This is just for one video. Just imagine the amount of videos available online. The numbers are beyond imaginable. All you need to do is just go to your favorite video site and grab that URL and give it to the tool. Rest of the heavy lifting is done by "Spookfish" tool for you. 

Yeah, enough of bragging about "Spookfish", Lets see it in action.

## About Implementation:
- Tool is based on  Client Server model.
- Client is [Wt](https://www.webtoolkit.eu/wt) (pronounced as Witty) C++ based Web Application acts as UI.
- Server is a pluggable Video analysis module. Each feature is pluggable module, hence design is modular and easy to add on any new feature.
- Client and Server use Json file formats to communicate.

### Video Analyzer

Video Analyzer is a Server module, which does all the heavy lifting of video processing. The idea is to keep the Analyzer on a powerful machine and the UI/Web Application to be hosted on any low end machine as a regular hosting platform. 
Each feature of interests can be easily added as a pluggable module to the Video analyzer. 

List of  supported features for this demo.
- Face Recognition.
- Face Clustering.
- Face Enrollment for the newly identified faces.
- Save all images in the cloud.
- Get Stats on the videos and images.

### UI
Now comes the most painful part of my project. I had never done any UI work in my life. So far. My experience was as a programmer was limited to writing CLI applications. Trust me, I never thought designing an UI was so difficult! So I took up the challenge, here is my "hello world" in to the Web application development!

There were couple of options which I tried out before settling on Wt. I tried PHP , Angular.js and Node.js. I really sucked at it all. Not because I couldn't understand it. But I was not able to achieve the expected results. I need more control on my application which I'm developing. Which I felt was lagging with those technologies. Then I knew, I need to do what I'm good at, so settled for C++ based Wt as my choice of app development.And I'm happy with my choice. It give more control and gives performance efficiencies which were pretty much required for this project to take it up to next level.

Once I got the hang of the Wt semantics I started building the app one component at a time. To my bad luck Wt had multiple versions and the default version which gets installed when you do sudo apt-get in ubuntu is 3.3.x, Which again was not helping me to get that wow factor with UI which I was hoping to get out of it. Then I realized I need to go with 4.x version of Wt. To my badluck, 3.x and 4.x was completely different. Many things have changed because 4.x uses C++14 features and I have to scrap the complete UI and start over. I re-did this UI three times to achieve the results which is being demonstrated below.

###### Step-1:

Launch the WebApp. Open your favorite browser, and type in "localhost:8080"

![SomeIMage](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/1.png?raw=true)
###### Step-2:
I've tried to keep things simple. All you need to do is go to youtube.com and select a video which you are interested in and enter it in the search bar. Hopefully with some actor/person's face in it :)

Once you hit the play button, lot of things happen behind the scene. To start with, the Youtube URL which you give in the search bar, is not playable as is. We need to find the original content URL. Some times it is called RTP playable URL of the original content. 

To get the playable RTP URL of the video. I've written some python code and used some python modules to achieve the same. You can find all the details in my [github link](https://github.com/Santhosh-KS/spookfish).

![Step-2](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/2.png?raw=true)

Now you are all set. There will be some basic validation on the URL. For this demo purpose, UI only takes in youtube URL. This could be changed to any other video source. You can even download the video and give it as input. But that is not the purpose of the Web Application tool. You can also build the VidoeAnalyser as a standalone application and use it to work as a Desktop like standalone application. This is as simple as commenting one line in `CMakeLists` file.

Like any Video player you get some very nice options
- play
- pause
- Change volume.
- Full screen.
- You can even download the youtube video which you are interested in! (Now that is cool.)
If you are a person with attention to details. You will notice that, when you play/pause respective icons and text will change accordingly to give you visual clue about what had happened. 


###### Step-3:

Once you hit the playbutton on the video search bar, There is nothing much you can do, but wait for the video analysis to complete. You can watch the video in full screen mode. Or you can take a break and come back. Depending on the system where you have deployed your analyzer, it takes its own time to complete. I've tried to implement the progress bar to show a visual indication of the current status of task. But that is not of much help currently.

But there is something which is useful and feels magical. You will get an updated processed images every 10 seconds! As shown below.

![step-3.1](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/3.png?raw=true)

As the video analysis progress, you keep getting new face image thumbnails. When you hover over the images, you can observe that each image is clickable. When you click an image, it takes you to the original image of the video frame,of which it was processed against.

![step-3.2](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/4.png?raw=true)


Once you click on any thumbnail, you get a new tab opened in your browser with the original image.

![step-3.3](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/5.png?raw=true)

If you go back to the thumbnail mode, you can observe that, it is not the raw image, but the image which is processed and identified that there is face in that image and image is cropped across the faces by taking the bounding rectangle, which was given by dlib's face recognition model (landmark 68 or 5) which we learnt as part of this course. 

There you go, now you have all the images with the bounding box details across the faces, just by couple of clicks. The bounding box information is not shown on the Image though, but in the background all the information related to the image is stored and maintained till the end of browsing session.

##### step-4:

Step 4 begins when all video analysis ends. Now you have multiple options. But next recommended feature is Image clustering. When we are done with step 3. There will be multiple images, cluttered all over, isn't it nice to create a collage of all the identified faces? All you need to do is just hit the `cluster` button on the Navigation bar. 

![step-4.1](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/6.png?raw=true)

Vola! There you go, all the identified faces are nicely clustered into one single image. You can toggle between all images and clustered images by pressing appropriate buttons on the Nav bar.

Again you can hover over each of the image thumbnails and click on individual images to see what is hidden under that thumbnail.

![step-4.2](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/9.png?raw=true)

That looks pretty neat. All the images are perfectly aligned with eyes and these clustered images are perfect for the emotion recognition features. 
You can also click on the clustered image and it will zoom in further.

##### step-5:
Once you have  clustered images, you can identify the images for training your new enrollment model. This portion I tried to automate by heavily depending on the Google Image search. Results were not so impressive. In fact certain results were too offensive and sexually explicit, on certain images and hence not suitable for kids who are under 18. You know what I mean ;). So I have  dropped the idea of reverse Google lookup on the images. And settled for user to input the character/person's name. 
If you are curious you can find the script doing the reverse Google lookup [here](https://github.com/Santhosh-KS/spookfish/tree/master/scripts).

![step-5.1](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/6.png?raw=true)

If you can notice there is an editable field called "Rename Me", user has the choice of giving what ever the name they like. There are couple of gotcha here.
- After entering the name user has to hit the `enter` key. 
- Don't give `<space>` character between firstname and last name. Instead use an '_' (under_score)  "Jon_Snow". 

*I Know bad UI choices! Hey, I'm not an UI expert.*

Once all the renaming is done we do create the folders with the name given here, if the name has some space character then that will cause some problem in creation of directories against that name.
Once you rename the actor's name background changes from red to green, just a visual clue to the user that name edit went fine. Now the, end results should look something like this.

![step-5.2](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/8.png?raw=true)


#### Step-6:
Oh god I wanted to create "Spookfish" but now I realized, I ended up creating a "Pandora box"! 
After step-5 you get a congratulation message about you opening up an Enrollment feature. You have successfully renamed all the person in the cluster block. Now you can create a new model by hitting the "Enroll" button on the Nav bar.

![step-6.1](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/10.png?raw=true)

As you can see, I'm really on time crunch and could not implement the visual clue to say Enrollment is done. Anyways you can see in the logs that Enrollment is done successfully. Now that creates the label_name.txt and descriptor.csv files in `/tmp/images/<sessionid>/` directory, you can pick those files and load any other video of the characters which were displayed in the cluster image, you will see all the images of characters identified as expected. Giving a single clustered image had improved the Enrollment part of the program significantly. It takes less than an second to Enroll on my system even with many cluster. There were few more thing which were there in my wish list, say create a master model on each run, but couldn't implement the same because of time constraints.

#### Step-7:
Now once we have all the required data, we are ready to get the stats of the video. Here is the snapshot of stats.

![step-7.1](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/11.png?raw=true)

This is just a really highlevel stats, I could come up in a day's time, I'm really pushing my luck against the time now. Next step is to make sense of these stats as explained earlier. Which is my next top on the TODO list.

#### Step-8 & 9:
So, the last but not the least step is to save the data and the images which are being captured. You can use any of your favorite cloud storage to store the images. For this demo purposes I've used [github](https://github.com/Santhosh-KS/ImageStorage) as my choice, as it was easy to store. You just need to configure it correctly to store it.
Here is the snapshot of directories which gets created and gets pushed in to the cloud storage.

![Step-8.1](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/12.JPG?raw=true)


You can also notice that the Names which we gave in Step-6 are created under faces directory which is used for Enrollment purposes.

![step-8.2](https://github.com/Santhosh-KS/ImageStorage/blob/master/ProjectReport/13.JPG?raw=true)

#### Final thoughts:


Spookfish is still in development stage and has its own share of bug/s and UI needs lot of polishing work. Despite of all that, it is shaping up in the right direction. There is definitely scope for improvement in many aspects, like the performance part and storing the image face_chips etc. With right amount of nurturing, I believe, it can evolve as a wonderful tool for the Computer Vision and AI community.

#### References:

Of course I'm really grateful to Satya, Vikas and [LearnOpencv](https://www.learnopencv.com/) team for making this course. Help me get myself upgraded, with the current technologies.

Along with the main course, this Project wouldn't have been possible, without the help of the following resource along with the content provided in the course.

- [MIT opensource course.](
https://www.youtube.com/watch?v=UtErkpTTmb8&index=38&t=0s&list=LLqF_WPfuINSogjD_rdNiqMQ
) Special thanks to Prof. Patrick H. Winston and the MIT open course for uploading Amazing video lectures.
And [Jessica Nose](https://www.youtube.com/watch?v=UtErkpTTmb8&index=38&t=0s&list=LLqF_WPfuINSogjD_rdNiqMQ) for uploading the follow up recitation lectures on the same. I don't know the name of the, TA who explains the problems and solutions in the video, she is certainly a great teacher.
- [3blue1brown](https://www.youtube.com/channel/UCYO_jab_esuFRV4b17AJtAw) for giving an amazing explanations and awesome intuition on the Calculus and linear algebra, through mind boggling animations. Huge Fan!
- [StatsLecture](https://www.youtube.com/watch?v=enQDKXI2PdA&index=84&list=LLqF_WPfuINSogjD_rdNiqMQ)  for giving an amazing overview of fundamentals fo statistics in 2 mins videos.
- [Wench lab](https://www.youtube.com/watch?v=efR8ybG7Ihs&t=0s&index=42&list=LLqF_WPfuINSogjD_rdNiqMQ) for wonderful explanation on the ML concepts.
- [Computer Philly](https://www.youtube.com/watch?v=yR7k19YBqiw&index=80&list=LLqF_WPfuINSogjD_rdNiqMQ) I really like the style and explanation provided in the video.
- [Santdex](https://www.youtube.com/channel/UCfzlCWGWYyIQ0aLC5w48gBQ) and [Socratica](https://www.youtube.com/channel/UCW6TXMZ5Pq6yL6_k5NZ2e0Q) for giving me great insight in to Python programming.
- [2mins paper](https://www.youtube.com/channel/UCbfYPyITQ-7l4upoX8nvctg). To keep me uptodate with the current happenings with AI technologies.
- [Wt tutorial by Victor Lavrenko](https://www.youtube.com/channel/UCs7alOMRnxhzfKAJ4JjZ7Wg) I wouldn't have dared to take up the UI design with Wt if I've not found these tutorials.

- UI would not have been possible, without the video lectures by  [EJ Media](https://www.youtube.com/channel/UC-JQzTHQrVA8j-tamvy66fw). I learnt about HTML, HTML5, CSS, Bootstrap, CSS grid and many more things. Thanks a ton for your simple and effective video series on each of these topics.

Last but not the least, OpenCV and DLib community, Without these communities this project would never seen the light of the day. In fact I'm planning to polish this UI and add in new features; and submit as a tool to DLib community.  Dlib's Image lab tool is a real inspiration for me to take up this project as a creation of tool rather than as a commercial application. Hope people start using and start contributing it to make it even better tool.

There are N number of websites and resources, I found useful in my development phase, unfortunately forgot to store most of them. If you find some thing which I've used from your blog/tutorial please drop me an [email](santhoshachar08@gmail.com), I would love to give credit for your work in this project.

 



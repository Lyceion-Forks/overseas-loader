# overseas-loader
A C++ CS:GO Cheat Loader for macOS

<b> Security is completely trash. It's not supposed to be good, it's just there. </b>

## How it works
First of all, it uses my admin panel, located <a href="https://github.com/gLevaa/moonlight-admin">here</a> for the serverside. The loader takes both the username and password from the user, then makes a request to the checks.php script on the serverside with the hwid, username and password which then returns a string which is either exploded by the loader into a token and a error/success code, or a error code related to what went wrong (incorrect username, hwid, etc.)

## Setup
First of all, you'll need a few things. 

<ul>
  <li>Basic programming knowledge</li>
  <li>A website capable of hosting the moonlight admin panel</li>
</ul>

As an alternative to a website, you could potentially host this off your own computer, look into XAMPP <a href="https://www.apachefriends.org/download.html">here</a>. However, I do not recommend this as it is a potential security risk given the relatively poor security of the corresponding admin panel.

<ol>
  <li>Now that you have these things, go over and setup the admin panel on your website, following the instructions on the admin panel repo.</li>
  <li>Now, take boostrap.dylib, your cheat dylib and compress it into a file named f.zip. Upload this into the loader directory in the panel.</li>
  <li>Go to line 100 of login.cpp and change the domain to whatever is needed.</li>
  <li>Go to line 35 of inject.cpp and change the domain to whatever is needed.</li>
  <li>Go to line 55 and change the param of Inject::inject() to whatever the name of your dylib is inside of f.zip</li>
</ol>

# Credits
<a href="https://github.com/pwnedboi/">pwned</a> for improving the code, suggesting ideas and helping with errors.<br>

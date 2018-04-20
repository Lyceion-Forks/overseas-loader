# overseas-loader
A C++ CS:GO Cheat Loader for macOS

## How it works
First of all, it uses my admin panel, located <a href="https://github.com/gLevaa/moonlight-admin">here</a> for the serverside. The loader takes both the username and password from the user, then makes a request to the checks.php script on the serverside with the hwid, username and password which then returns a string which is either exploded by the loader into a token and a error/success code, or a error code related to what went wrong (incorrect username, hwid, etc.)

# Setup
First of all, you'll need a few things. 

<ul>
  <li>Basic programming knowledge</li>
  <li>A website capable of hosting the moonlight admin panel</li>
</ul>

As an alternative to a website, you could potentially host this off your own computer, look into XAMPP <a href="https://www.apachefriends.org/download.html">here</a>. However, I do not recommend this as it's a huge security risk and overall stupid.

<ol>
  <li>Now that you have these things, go over and setup the admin panel on your website, following the instructions on the admin panel repo.</li>
  <li>Now, take osxinj, boostrap.dylib, your cheat dylib and compress it into a file named f.zip. Upload this into the loader directory in the panel.</li>
  <li>Go to line 63 of main.cpp and change the domain to whatever is needed.</li>
  <li>Go to line 66 of main.cpp and change the paramater of login->inject to the name of your dylib which is in the f.zip file.</li>
  <li>Go to line 28 of login.cppand change the domain to whatever is needed.</li>
</ol>

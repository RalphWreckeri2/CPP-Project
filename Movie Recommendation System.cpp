#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

//GLOBAL
int secondUserChoice; // Variable for cin (in nested conditions in functions)
queue<string> userMovieQueue; //For queue in USER LIST

// Define a structure to represent a movie
struct Movie {
    string title;
    string genre;
    string trope;
    string stars;
};

// Sorting and Searching Technique
void merge(Movie* arr, int left, int mid, int right);
void mergeSort(Movie* arr, int left, int right);
int findGenreIndex(const string& selectedGenre, const string* genres, int numGenres);

// Function prototypes
void home();
void userList();
void chooseGenres();
void chooseTropes(const string& selectedGenre);
void displayMoviesBasedOnTrope(const string& selectedGenre, int tropeChoice);

// Function for error handlings para iwas redundancy
void goodbyeExit();

//LOG IN
class userLog {
public:
    string username;
    string password;
    int age;

    userLog() {};

    userLog(string uname, string pwd, int userAge) {
        username = uname;
        password = pwd;
        age = userAge;
    }
};

class userManagement {
private:
    userLog currentUser;

public:
    userManagement(string uname, string pwd, int userAge) {
        currentUser = userLog(uname, pwd, userAge);
    }

    bool logIn(string uname, string pwd, int userAge) {
        if (uname == currentUser.username && pwd == currentUser.password && userAge >= 18) {
            return true;
        }
        else if (userAge < 18) {
            cout << endl;
            cout << "    ======================================================" << endl;
            cout << "    ||                                                  ||" << endl;
            cout << "    || Sorry, you are not eligible to use this program. ||" << endl;
            cout << "    || We'll try and come up a better program for you!! ||" << endl;
            cout << "    ||                                                  ||" << endl;
            cout << "    ======================================================" << endl;
            exit(0);
            return false;
        }
        else {
            cout << endl << endl;
            cout << "    ======================================================" << endl;
            cout << "    ||  Invalid Username or Password. Please try again. ||" << endl;
            cout << "    ======================================================" << endl;
            return false;
        }
    }
};

// Storage of information using array
const int numGenres = 5;
const string genres[numGenres] = { "Action", "Comedy", "Drama", "Romance", "Science Fiction" };

const int numTropes = 5;
string tropes[5][numTropes] = {
    // Action tropes
    {"The Hero's Journey", "The Chase Scene", "The MacGuffin", "The Explosive Climax", "The Last Stand"},
    // Comedy tropes
    {"Fish Out of Water", "Buddy Comedy", "Screwball Comedy", "Romantic Comedy", "Parody or Spoof"},
    // Drama tropes
    {"Family Drama", "Legal Drama", "Psychological Drama", "Romantic Drama", "Biographical Drama"},
    // Romance tropes
    {"First Love", "Friends to Lovers", "Enemies to Lovers", "Forbidden Love", "Second CHance Romance"},
    // Science Fiction tropes
    {"Artificial Intelligence | Robot", "Time Travel", "Aliens", "The Time Travel Paradox", "Alien Invasion"}
};

Movie actionTropeOne[5] = {
    {"The Matrix Resurrections", "Action", "The Hero's Journey", "Keanu Reeves, Laurence Fishburne & Carrie-Anne Moss"},
    {"Pirates of the Caribbean: The Curse of the Black Pearl", "Action", "The Hero's Journey", "Johnny Depp, Orlando Bloom & Keira Knightley"},
    {"The Hobbit: An Unexpected Journey", "Action", "The Hero's Journey", "Martin Freeman, Ian McKellen & Richard Armitage"},
    {"Wonder Woman 1984", "Action", "The Hero's Journey", "Gal Gadot, Chris Pine & Connie Nielsen"},
    {"The Lion King", "Action", "The Hero's Journey", "Matthew Broderick, Nathan Lane & Ernie Sabella"}
};

Movie actionTropeTwo[5] = {
    {"The Italian Job", "Action", "The Chase Scene", "Mark Wahlberg, Charlize Theron & Edward Norton"},
    {"Mad Max: Fury Road", "Action", "The Chase Scene", "Tom Hardy, Charlize Theron & Nicholas Hoult"},
    {"The French Connection", "Action", "The Chase Scene", "Gene Hackman, Roy Scheider & Fernando Rey"},
    {"Fast Five", "Action", "The Chase Scene", "Vin Diesel, Paul Walke & Dwayne Johnson"},
    {"Terminator 2: Judgement Day", "Action", "The Chase Scene", "Linda Hamilton, Edward Furlong & Arnold Schwarzenegger"}
};

Movie actionTropeThree[5] = {
    {"Indiana Jones and the Kingdom of the Crystal Skull", "Action", "The MacGuffin", "Harrison Ford, Karen Allen & Denholm Elliott"},
    {"National Treasure: Edge of History", "Action", "The MacGuffin", "Nicolas Cage, Diane Kruger & Justin Bartha"},
    {"The Maltese Falcon", "Action", "The MacGuffin", "Humphrey Bogart, Mary Astor & Peter Lorre"},
    {"Mission: Impossible - Dead Reckoning Part Two", "Action", "The MacGuffin", "Tom Cruise, Jon Voight & Emmanuelle Béart"},
    {"The Avengers", "Action", "The MacGuffin", " Robert Downey Jr., Chris Evans & Chris Hemsworth"}
};

Movie actionTropeFour[5] = {
    {"The Dark Knight", "Action", "The Explosive Climax", "Christian Bale, Heath Ledger & Aaron Eckhart"},
    {"200 Motels", "Action", "The Explosive Climax", "Leonardo DiCaprio, Joseph Gordon-Levitt & Ellen Page"},
    {"Mad Max: Fury Road", "Action", "The Explosive Climax", "Tom Hardy, Charlize Theron & Nicholas Hoult"},
    {"The Avengers: Earth's Mightiest Heroes!", "Action", "The Explosive Climax", "Robert Downey Jr., Chris Evans & Scarlett Johansson"},
    {"Die Hard With a Vengeance", "Action", "The Explosive Climax", "Bruce Willis, Samuel L. Jackson & Jeremy Irons"}
};

Movie actionTropeFive[5] = {
    {"300 Nassau", "Action", "The Last Stand", "King Leonidas, Queen Gorgo & Xerxes"},
    {"The Alamo ", "Action", "The Last Stand", "Davy Crockett, Jim Bowie & William Travis"},
    {"Black Hawk Down", "Action", "The Last Stand", "Staff Sergeant Matt Eversmann, Sergeant First Class Norm Gibson & Lieutenant Colonel Danny McKnight"},
    {"The Magnificent Seven", "Action", "The Last Stand", "Chris Adams, Vin Tanner & Chico"},
    {"Hacksaw Ridge", "Action", "The Last Stand", "Desmond Doss, Sergeant Howell & Captain Glover"}
};

// Comedy
Movie comedyTropeOne[5] = {
    {"Coming to America", "Comedy", "Fish out of Water", "Eddie Murphy, Arsenio Hall & Shari Headley"},
    {"Elf Me", "Comedy", "Fish out of Water", "Will Ferrell, James Caan & Zooey Deschanel"},
    {"The Blues Brothers", "Comedy", "Fish out of Water", "John Belushi, Dan Aykroyd & Kathleen Freeman"},
    {"Crocodile Dundee in Los Angeles", "Comedy", "Fish out of Water", "Paul Hogan, Linda Kozlowski & John Meillon"},
    {"The Jerk Theory", "Comedy", "Fish out of Water", "Steve Martin, Bernadette Peters & M. Emmet Walsh"}
};

Movie comedyTropeTwo[5] = {
    {"Dumb and Dumber To", "Comedy", "Buddy Comedy", "Jim Carrey, Jeff Daniels & Lauren Holly"},
    {"Superbad", "Comedy", "Buddy Comedy", "Jonah Hill, Michael Cera & Christopher Mintz-Plasse"},
    {"Step Brothers", "Comedy", "Buddy Comedy", "Will Ferrell, John C. Reilly & Mary Steenburgen"},
    {"Rush Hour", "Comedy", "Buddy Comedy", "Jackie Chan, Chris Tucker & Julia Hsu"},
    {"Planes, Trains and Automobiles", "Comedy", "Buddy Comedy", "Steve Martin, John Candy & Laila Robins"}
};

Movie comedyTropeThree[5] = {
    {"It's Like, You Know ... ", "Comedy", "Screwball Comedy", "Tony Curtis, Jack Lemmon & Marilyn Monroe"},
    {"Bringing Up Baby", "Comedy", "Screwball Comedy", "Katharine Hepburn, Cary Grant & May Robson"},
    {"His Girl Friday", "Comedy", "Screwball Comedy", "Cary Grant, Rosalind Russell & Ralph Bellamy"},
    {"It Happened One Night", "Comedy", "Screwball Comedy", "Claudette Colbert, Clark Gable & Walter Connolly"},
    {"The Lady Eve", "Comedy", "Screwball Comedy", "Barbara Stanwyck, Henry Fonda & Charles Coburn"}
};

Movie comedyTropeFour[5] = {
    {"When Harry Met Sally", "Comedy", "Romantic Comedy", "Billy Crystal, Meg Ryan & Carrie Fisher"},
    {"The Proposal Spot", "Comedy", "Romantic Comedy", "Sandra Bullock, Ryan Reynolds & Betty White"},
    {"10 Things I Hate About You", "Comedy", "Romantic Comedy", "Julia Stiles, Heath Ledger & Joseph Gordon-Levitt"},
    {"Crazy, Stupid, Love", "Comedy", "Romantic Comedy", "Steve Carell, Ryan Gosling & Julianne Moore"},
    {"Notting Hill", "Comedy", "Romantic Comedy", "Hugh Grant, Julia Roberts & Rhys Ifans"}
};

Movie comedyTropeFive[5] = {
    {"Airplane Mode", "Comedy", "Parody or Spoof", "Robert Hays, Julie Hagerty & Leslie Nielsen"},
    {"Search Results", "Comedy", "Parody or Spoof", "Bill Pullman, John Candy & Daphne Zuniga"},
    {"Robin Hood: Men in Tights", "Comedy", "Parody or Spoof", "Cary Elwes, Amy Yasbeck & Roger Rees"},
    {"Austin Powers: International Man of Mystery", "Comedy", "Parody or Spoof", "Mike Myers, Mike Myers & Elizabeth Hurley"},
    {"The Hungover Games", "Comedy", "Parody or Spoof", "Rita Volk, Ben Begley & Jamie Kennedy"}
};

// Drama
Movie dramaTropeOne[5] = {
    {"The Godfather (1972)", "Drama", "Family Drama", "Vito Corleone, Michael Corleone, Sonny Corleon"},
    {"American Beauty (1999)", "Drama", "Legal Drama", "Lester Burnham, Carolyn Burnham, Jane Burnham"},
    {"Little Miss Sunshine(2006)", "Drama", "Psychological Drama", "Olive Hoover, Richard Hoover, Sheryl Hoover"},
    {"August: Osage Country (2013)", "Drama", "Romantic Drama", "Violet Weston, Barbara Weston, Bill Fordham"},
    {"Manchester by the Sea (2016)", "Drama", "Biographical Drama", "Lee Chandler, Patrick Chandler, Randi Chandler"}
};

Movie dramaTropeTwo[5] = {
    {"A Few Good Men (1992)", "Drama", "Legal Drama", "Daniel Kaffee, JoAnne Galloway & Nathan Jessup"},
    {"Philadelphia (1993)", "Drama", "Legal Drama", "Andrew Beckett, Joe Miller & Sarah Beckett"},
    {"Erin Brockovich (2000)", "Drama", "Legal Drama", "Erin Brockovich, Ed Masry & George"},
    {"A Time to Kill (1996)", "Drama", "Legal Drama", "Jake Brigance, Carl Lee Hailey & Ellen Roark"},
    {"The Judge (2014)", "Drama", "Legal Drama", "Hank Palmer, Joseph Palmer & Glen Palmer"}
};

Movie dramaTropeThree[5] = {
    {"Black Swan (2010)", "Drama", "Psychological Drama", "Nina Sayers, Thomas Leroy & Lily"},
    {"Shutter Island (2010)", "Drama", "Psychological Drama", "Teddy Daniels, Chuck Aule & Dr. John Cawley"},
    {"Requiem for a Dream (2000)", "Drama", "Psychological Drama", "Harry Goldfarb, Marion Silver & Tyrone Love"},
    {"Fight Club (1999)", "Drama", "Psychological Drama", "The Narrator, Tyler Durden & Marla Singer"},
    {"Memento (2000)", "Drama", "Psychological Drama", "Leonard Shelby, Teddy Gammell & Natalie"}
};

Movie dramaTropeFour[5] = {
    {"The Notebook (2004)", "Drama", "Romantic Drama", "Noah Calhoun, Allie Hamilton & Lon Hammond Jr."},
    {"Titanic (1997)", "Drama", "Romantic Drama", "Jack Dawson, Rose DeWitt Bukater & Cal Hockley"},
    {"A Walk to Remember (2002)", "Drama", "Romantic Drama", "Landon Carter, Jamie Sullivan & Reverend Sullivan"},
    {"Brokeback Miuntain (2005)", "Drama", "Romantic Drama", "Ennis Del Mar, Jack Twist & Alma Beers"},
    {"The Fault in our Stars (2014)", "Drama", "Romantic Drama", "Hazel Grace Lancaster, Augustus Waters & Isaac"}
};

Movie dramaTropeFive[5] = {
    {"Schindler's List (1993)", "Drama", "Biographical Drama", "Oskar Schindler, Itzhak Stern & Amon Göth"},
    {"The Social Network (2010)", "Drama", "Biographical Drama", "Mark Zuckerberg, Eduardo Saverin & Sean Parker"},
    {"The Pursuit of Happyness (2006)", "Drama", "Biographical Drama", "Chris Gardner, Christopher Jr. & Linda"},
    {"Ray (2004)", "Drama", "Biographical Drama", "Ray Charles, Della Bea Robinson & Quincy Jones"},
    {"The King's Speech (2010)", "Drama", "Biographical Drama", "King George VI, Lionel Logue & Queen Elizabeth"}
};

// Romance
Movie romanceTropeOne[5] = {
    {"Flipped", "Romance", "First Love", "Madeline Caroll & Callan McAullife"},
    {"A Walk to Remember", "Romance", "First Love", "Many Moore & Shane West"},
    {"The Fault in our Stars", "Romance", "First Love", "Shailene Woodley & Ansel Elgort"},
    {"Moonrise Kingdom", "Romance", "First Love", "Jared Gilman & Kara Hayward"},
    {"The Perks of Being a Wallflower", "Romance", "First Love", "Emma Watson, Logan Lerman & Ezra Miller"}
};

Movie romanceTropeTwo[5] = {
    {"High School Musical", "Romance", "Friends to Lovers", "Vanessa Hudgens & Zac Efron"},
    {"When Harry Met Sally", "Romance", "Friends to Lovers", "Harry Burns, Sally Albright & Marie"},
    {"Just Friends", "Romance", "Friends to Lovers", "Chris Brander, Jamie Palamino & Samantha James"},
    {"Someone Like You", "Romance", "Friends to Lovers", "Jane Goodale, Eddie Alden & Ray Brown"},
    {"My Best Friend's Wedding", "Romance", "Friends to Lovers", "Julianne Potter, Michael O'Neal & immy Wallace"}
};

Movie romanceTropeThree[5] = {
    {"Pride and Prejudice: A New Musical", "Romance", "Enemies to Lovers", ""},
    {"You've Got Mail", "Romance", "Enemies to Lovers", "Kathleen Kelly, Joe Fox & Patricia Eden"},
    {"Diary ng Panget", "Romance", "Enemies to Lovers", "Nadine Lustre & James Reid"},
    {"She's Dating the Gangster", "Romance", "Enemies to Lovers", "Kathryn Bernardo & Daniel Padilla"},
    {"Clueless", "Romance", "Enemies to Lovers", "Alicia Silverstone, Paul Rudd & Brittany Murphy"}
};

Movie romanceTropeFour[5] = {
    {"Romeo Juliet", "Romance", "Forbidden Love", "Romeo Montague, Juliet Capulet, Mercutio"},
    {"Brokeback Mountain", "Romance", "Forbidden Love", "Ennis Del Mar, Jack Twist, Alma Beers"},
    {"Titanic: 25th Anniversary", "Romance", "Forbidden Love", "Jack Dawson, Rose DeWitt Bukater, Cal Hockley"},
    {"The Notebook", "Romance", "Forbidden Love", "Noah Calhoun, Allie Hamilton, Lon Hammond Jr."},
    {"Atonement", "Romance", "Forbidden Love", "Robbie Turner, Cecilia Tallis & Briony Tallis"}
};

Movie romanceTropeFive[5] = {
    {"Serendipity", "Romance", "Second Chance Romance", "Jonathan Trager, Sara Thomas & Dean Kansky"},
    {"Sweet Home Alabama", "Romance", "Second Chance Romance", "Melanie Carmichael, Jake Perry & Andrew Hennings"},
    {"Definitely, Maybe", "Romance", "Second Chance Romance", "Will Hayes, April Hoffman & Summer Hartley"},
    {"P.S. I love You", "Romance", "Second Chance Romance", "Holly Kennedy, Gerry Kennedy & William Gallagher"},
    {"A Second Chance", "Romance", "Second Chance Romance", "Jhon Lloyd Cruz & Bea Alonzo"}
};

// Sci-Fi
Movie scifiTropeOne[5] = {
    {"JungE", "Sci-Fi", "Artificial Intelligence | Robot", ""},
    {"A.I. Artificial Intelligence", "Sci-Fi", "Artificial Intelligence | Robot", ""},
    {"Tau", "Sci-Fi", "Artificial Intelligence | Robot", ""},
    {"Archive", "Sci-Fi", "Artificial Intelligence | Robot", ""},
    {"Space Sweepers", "Sci-Fi", "Artificial Intelligence | Robot", ""}
};

Movie scifiTropeTwo[5] = {
    {"The Adama Project", "Sci-Fi", "Time Travel", ""},
    {"The Tomorrow War", "Sci-Fi", "Time Travel", ""},
    {"Terminator Genisys", "Sci-Fi", "Time Travel", ""},
    {"Predestination", "Sci-Fi", "Time Travel", ""},
    {"Looper", "Sci-Fi", "Time Travel", ""}
};

Movie scifiTropeThree[5] = {
    {"E.T. The Extra Terrestrial", "Sci-Fi", "Aliens", ""},
    {"Avatar", "Sci-Fi", "Aliens", ""},
    {"The 5th Wave", "Sci-Fi", "Aliens", "Chloe Grace Moretz & Alex Roe"},
    {"Alienoid", "Sci-Fi", "Aliens", "Kim Tae-ri, Ryu Jun-Yeol & Kim Woo-Bin"},
    {"Paul", "Sci-Fi", "Aliens", "Simon Pegg, Nick Frost & Seth Rogen (voice)"}
};

Movie scifiTropeFour[5] = {
    {"Back to the Future", "Sci-Fi", "The Time Travel Paradox", "Michael J. Fox, Christopher Lloyd & Crispin Glover"},
    {"Why Me 2021", "Sci-Fi", "The Time Travel Paradox", "Joseph Gordon-Levitt, Bruce Willis & Emily Blunt"},
    {"The Terminator", "Sci-Fi", "The Time Travel Paradox", "Linda Hamilton, Michael Biehn, Arnold Schwarzenegger"},
    {"Primer día", "Sci-Fi", "The Time Travel Paradox", "Shane Carruth, David Sullivan Samantha Thomson"},
    {"Edge of Tomorrow", "Sci-Fi", "The Time Travel Paradox", "Tom Cruise, Emily Blunt & Bill Paxton"}
};

Movie scifiTropeFive[5] = {
    {"Independence Day: Resurgence", "Sci-Fi", "Alien Invasion", "Will Smith, Bill Pullman & Jeff Goldblum"},
    {"District 9", "Sci-Fi", "Alien Invasion", "Tom Cruise, Dakota Fanning & Justin Chatwin"},
    {"District 9 (2009)", "Sci-Fi", "Alien Invasion", "Sharlto Copley, Jason Cope & Vanessa Haywood"},
    {"Arrival ", "Sci-Fi", "Alien Invasion", "Amy Adams, Jeremy Renner & Forest Whitaker"},
    {"Battle: Los Angeles", "Sci-Fi", "Alien Invasion", "Aaron Eckhart, Cory Hardrict), Lieutenant William  & Fdiane"}
};

// Main function
int main() {

    string username, password;
    int age;
    cout << endl << endl;
    cout << "    =====================================================" << endl;
    cout << "    ||                                                 ||" << endl;
    cout << "    ||  WELCOME TO CINENG MALAYA: PICK ME, CHOOSE ME!  ||" << endl;
    cout << "    ||        Kindly Sign in to use the program.       ||" << endl;
    cout << "    ||                                                 ||" << endl;
    cout << "    =====================================================" << endl;
    cout << "    |||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "    =====================================================" << endl;
    cout << "    ||    Note: You must be 18+ to use the program     ||" << endl;
    cout << "    =====================================================" << endl << endl;
    cout << "    ----->     Enter username: ";
    cin >> username;
    cout << "    ----->     Enter password: ";
    cin >> password;
    cout << "    ----->     Enter your age: ";
    cin >> age;

    userManagement userManager("GroupOne", "PogiSiMatt", 18); 

    if (userManager.logIn(username, password, age)) {
        system("CLS");
        home();
    }

    return 0;
}
// End of Main Function

// GOODBYE function
void goodbyeExit() {
    system("CLS");
    cout << endl << endl;
    cout << "    ===============================================" << endl;
    cout << "    ||                                           ||" << endl;
    cout << "    ||     We're sad to see you go. Goodbye!     ||" << endl;
    cout << "    ||                   :(                      ||" << endl;
    cout << "    ||                                           ||" << endl;
    cout << "    ===============================================" << endl;
    exit(0);
}

// HOME function
void home() {

    cout << endl << endl;
    cout << "    ===================================================" << endl;
    cout << "    ||                                               ||" << endl;
    cout << "    ||                  WELCOME TO                   ||" << endl;
    cout << "    ||   PERSONALIZED MOVIE RECOMMENDATION SYSTEM    ||" << endl;
    cout << "    ||  This C++ Program recommends movies to users  ||" << endl;
    cout << "    ||  based on their age, chosen genre, and trope. ||" << endl;
    cout << "    ||                                               ||" << endl;
    cout << "    ===================================================" << endl;
    cout << "    |||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "    ===================================================" << endl;
    cout << "    ||       DISCOVER YOUR NEXT FAVORITE MOVIE!      ||" << endl;
    cout << "    ===================================================" << endl << endl;
    cout << "        [1] CONTINUE     [2] MY LIST     [3] EXIT      " << endl << endl;
    int userChoice;
    cout << "                      Your choice: ";
    cin >> userChoice;

    if (userChoice == 1) {
        system("CLS");
        chooseGenres();
    }
    else if (userChoice == 2) {
        system("CLS");
        userList();
    }
    else if (userChoice == 3) {
        goodbyeExit();
    }
    //For invalid answers (e.g. 3, 4...)
    else {
        do {
            system("CLS");

            cout << endl << endl;
            cout << "                Invalid choice. Try again.             " << endl;
            cout << "                --------------------------             " << endl << endl;
            cout << "    ===================================================" << endl;
            cout << "    ||                                               ||" << endl;
            cout << "    ||                  WELCOME TO                   ||" << endl;
            cout << "    ||   PERSONALIZED MOVIE RECOMMENDATION SYSTEM    ||" << endl;
            cout << "    ||  This C++ Program recommends movies to users  ||" << endl;
            cout << "    ||  based on their age, chosen genre, and trope. ||" << endl;
            cout << "    ||                                               ||" << endl;
            cout << "    ===================================================" << endl;
            cout << "    |||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
            cout << "    ===================================================" << endl;
            cout << "    ||       DISCOVER YOUR NEXT FAVORITE MOVIE!      ||" << endl;
            cout << "    ===================================================" << endl << endl << endl;

            cout << "          Press [1] to Continue and [2] to Exit: ";
            cin >> secondUserChoice;
            if (secondUserChoice == 1) {
                if (secondUserChoice == 1) {
                    system("CLS");
                    chooseGenres();
                }
            }
            else if (secondUserChoice == 2) {
                goodbyeExit();
            }
        } while (secondUserChoice != 1 && secondUserChoice != 2);
    }
}

void userList() {
    cout << endl << endl;
    cout << "    --------------------------------------------------------------" << endl;
    cout << "    |                                                            |" << endl;
    cout << "    |                     YOUR WATCHED MOVIES                    |" << endl;
    cout << "    |  This section gathers the lists of the movies you watched  |" << endl;
    cout << "    |                                                            |" << endl;
    cout << "    --------------------------------------------------------------" << endl;

    if (userMovieQueue.empty()) {
        cout << "                         No movies watched yet." << endl;
    }
    else {
        queue<string> tempQueue = userMovieQueue;
        int count = 1;
        while (!tempQueue.empty()) {
            cout << "        " << count++ << ". " << tempQueue.front() << endl;
            tempQueue.pop();
        }
    }

    cout << endl << endl;
    cout << "    --------------------------------------------------------------" << endl;
    cout << "    [1] HOME               [2] DELETE A MOVIE             [3] EXIT" << endl;
    cout << "    --------------------------------------------------------------" << endl;
    int userChoice;
    cout << "                            YOUR CHOICE: ";
    cin >> userChoice;

    if (userChoice == 1) {
        system("CLS");
        home();
    }
    else if (userChoice == 2) {
        if (!userMovieQueue.empty()) {
            cout << endl;
            cout << "    Enter the number of the movie you want to delete: ";
            int movieToDelete;
            cin >> movieToDelete;

            if (movieToDelete >= 1 && movieToDelete <= userMovieQueue.size()) {
                queue<string> tempQueue2;
                while (movieToDelete > 1) {
                    tempQueue2.push(userMovieQueue.front());
                    userMovieQueue.pop();
                    movieToDelete--;
                }
                userMovieQueue.pop();
                while (!tempQueue2.empty()) {
                    userMovieQueue.push(tempQueue2.front());
                    tempQueue2.pop();
                }
                cout << endl;
                cout << "    Movie deleted successfully." << endl;
                cout << endl;

                int userChoice2;
                cout << "    Press [1] to Continue and [2] to Exit: ";
                cin >> userChoice2;

                if (userChoice2 == 1) {
                    system("CLS");
                    home();
                }
                else if (userChoice2 == 2) {
                    system("CLS");
                    goodbyeExit();
                }
                else {
                    system("CLS");
                    cout << endl << endl;
                    cout << "    Invalid Choice. You are now on the exit. Goodbye!" << endl;
                    goodbyeExit();
                }
            }
            else {
                system("CLS");
                cout << endl << endl;
                cout << "    Invalid movie number. You are now on the exit. Goodbye!" << endl;
                goodbyeExit();
            }
        }
        else {
            system("CLS");
            cout << endl << endl;
            cout << "        No movies to delete. Returning to homepage." << endl;
            home();
        }
    }
    else if (userChoice == 3) {
        goodbyeExit();
    }
    else {
        int secondUserChoice;
        do {
            cout << endl << endl;
            cout << "    --------------------------------------------------------------" << endl;
            cout << "    [1] HOME               [2] DELETE A MOVIE             [3] EXIT" << endl;
            cout << "    --------------------------------------------------------------" << endl;
            cout << "                            YOUR CHOICE: ";
            cin >> secondUserChoice;
            if (secondUserChoice == 1) {
                system("CLS");
                home();
            }
            else if (secondUserChoice == 2) {
                if (!userMovieQueue.empty()) {
                    cout << "    Enter the number of the movie you want to delete: ";
                    int movieToDelete;
                    cin >> movieToDelete;

                    if (movieToDelete >= 1 && movieToDelete <= userMovieQueue.size()) {
                        queue<string> tempQueue2;
                        while (movieToDelete > 1) {
                            tempQueue2.push(userMovieQueue.front());
                            userMovieQueue.pop();
                            movieToDelete--;
                        }
                        userMovieQueue.pop();
                        while (!tempQueue2.empty()) {
                            userMovieQueue.push(tempQueue2.front());
                            tempQueue2.pop();
                        }
                        cout << "    Movie deleted successfully." << endl;
                    }
                    else {
                        cout << "    Invalid movie number." << endl;
                    }
                }
                else {
                    cout << "    No movies to delete." << endl;
                }
                cout << "    Press [1] to Continue and [3] to Exit: ";
                cin >> secondUserChoice;
                if (secondUserChoice == 1) {
                    system("CLS");
                    home();
                }
                else if (secondUserChoice != 3) {
                    cout << "    Invalid Choice. You are now on the exit. Goodbye!" << endl;
                    goodbyeExit();
                }
            }
            else if (secondUserChoice == 3) {
                goodbyeExit();
            }
        } while (secondUserChoice != 1 && secondUserChoice != 3);
    }
}

// Searching technique
int findGenreIndex(const string& selectedGenre, const string* genres, int numGenres) {
    for (int i = 0; i < numGenres; ++i) {
        if (genres[i] == selectedGenre) {
            return i;
        }
    }
    return -1;
}

// CHOOSING A GENRE function
void chooseGenres() {

    cout << endl;
    cout << "      ===================================================" << endl;
    cout << "      ||                                               ||" << endl;
    cout << "      || YOU ARE TWO STEPS CLOSER TO CHOOSING A MOVIE! ||" << endl;
    cout << "      ||               CHOOSE YOUR GENRE :             ||" << endl;
    cout << "      ||                                               ||" << endl;
    cout << "      ===================================================" << endl;

    for (int i = 0; i < numGenres; ++i) {
        cout << "                   " << (i + 1) << ". " << genres[i] << "                      " << endl;
    }

    cout << "      ===================================================" << endl;

    int choice;
    cout << endl << "         Enter the number of your preferred genre: ";
    cin >> choice;

    string selectedGenre;
    if (choice >= 1 && choice <= numGenres) {
        selectedGenre = genres[choice - 1];
    }
    else {
        system("CLS");
        cout << endl << endl << "    Invalid genre choice. Redirecting you back to the page." << endl;
        cout << endl << "    -------------------------------------------------------" << endl;
        chooseGenres();
        return;
    }

    system("CLS");
    chooseTropes(selectedGenre);
}

// CHOOSING A TROPE function
void chooseTropes(const string& selectedGenre) {
    int genreIndex = findGenreIndex(selectedGenre, genres, numGenres);
    if (genreIndex == -1) {
        cout << "Invalid genre selected." << endl;
        return;
    }

    cout << endl << endl;
    cout << "         ====================================================" << endl;
    cout << "         ||               YOU'RE ALMOST THERE!             ||" << endl;
    cout << "         ====================================================" << endl;
    cout << "         --->  Select a trope for " << selectedGenre << " movies:" << endl;
    cout << "         ----------------------------------------------------" << endl << endl;
    for (int i = 0; i < numTropes; i++) {
        if (!tropes[genreIndex][i].empty()) {
            cout << "          " << i + 1 << ". " << tropes[genreIndex][i] << endl;
        }
    }
    cout << endl << "         ---------------------------------------------------- " << endl;

    int userChoice;
    cout << "         ----------------------------------------------------" << endl;
    cout << "         [1] GO BACK           [2] PROCEED           [3] EXIT" << endl;
    cout << "         ----------------------------------------------------" << endl;
    cout << "                             YOUR CHOICE: ";
    cin >> userChoice;

    switch (userChoice) {
    case 1:
        system("CLS");
        chooseGenres();
        break;
    case 2: {
        int tropeChoice;
        cout << "         ----------------------------------------------------" << endl << endl;
        cout << "             Enter the number of your preferred trope: ";
        cin >> tropeChoice;

        system("CLS");
        displayMoviesBasedOnTrope(selectedGenre, tropeChoice);
        break;
    }
    case 3:
        goodbyeExit();
        break;
    default:
        system("CLS");
        cout << endl << endl;
        cout << "              Invalid choice. Redirecting you to the page." << endl;
        cout << "              -------------------------------------------";
        chooseTropes(selectedGenre);
    }
}

// Sorting Technique
void merge(Movie* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Movie* L = new Movie[n1];
    Movie* R = new Movie[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].title <= R[j].title)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(Movie* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// DISPLAYING function
void displayMoviesBasedOnTrope(const string& selectedGenre, int tropeChoice) {

    cout << endl << endl;
    cout << "    ==============================================================" << endl;
    cout << "    ||          HERE ARE THE MOVIES CATERED FOR YOU             ||" << endl;
    cout << "    ||                    ENJOY PICKING !!!                     ||" << endl;
    cout << "    ==============================================================" << endl;
    cout << "    ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;

    Movie* selectedMovies = nullptr; 
    int numMovies;

    switch (tropeChoice) {
    case 1:
        if (selectedGenre == "Action") {
            selectedMovies = actionTropeOne;
        }
        else if (selectedGenre == "Comedy") {
            selectedMovies = comedyTropeOne;
        }
        else if (selectedGenre == "Drama") {
            selectedMovies = dramaTropeOne;
        }
        else if (selectedGenre == "Romance") {
            selectedMovies = romanceTropeOne;
        }
        else if (selectedGenre == "Science Fiction") {
            selectedMovies = scifiTropeOne;
        }
        numMovies = 5;
        break;
    case 2:
        if (selectedGenre == "Action") {
            selectedMovies = actionTropeTwo;
        }
        else if (selectedGenre == "Comedy") {
            selectedMovies = comedyTropeTwo;
        }
        else if (selectedGenre == "Drama") {
            selectedMovies = dramaTropeTwo;
        }
        else if (selectedGenre == "Romance") {
            selectedMovies = romanceTropeTwo;
        }
        else if (selectedGenre == "Science Fiction") {
            selectedMovies = scifiTropeTwo;
        }
        numMovies = 5;
        break;
    case 3:
        if (selectedGenre == "Action") {
            selectedMovies = actionTropeThree;
        }
        else if (selectedGenre == "Comedy") {
            selectedMovies = comedyTropeThree;
        }
        else if (selectedGenre == "Drama") {
            selectedMovies = dramaTropeThree;
        }
        else if (selectedGenre == "Romance") {
            selectedMovies = romanceTropeThree;
        }
        else if (selectedGenre == "Science Fiction") {
            selectedMovies = scifiTropeThree;
        }
        numMovies = 5;
        break;
    case 4:
        if (selectedGenre == "Action") {
            selectedMovies = actionTropeFour;
        }
        else if (selectedGenre == "Comedy") {
            selectedMovies = comedyTropeFour;
        }
        else if (selectedGenre == "Drama") {
            selectedMovies = dramaTropeFour;
        }
        else if (selectedGenre == "Romance") {
            selectedMovies = romanceTropeFour;
        }
        else if (selectedGenre == "Science Fiction") {
            selectedMovies = scifiTropeFour;
        }
        numMovies = 5;
        break;
    case 5:
        if (selectedGenre == "Action") {
            selectedMovies = actionTropeFive;
        }
        else if (selectedGenre == "Comedy") {
            selectedMovies = comedyTropeFive;
        }
        else if (selectedGenre == "Drama") {
            selectedMovies = dramaTropeFive;
        }
        else if (selectedGenre == "Romance") {
            selectedMovies = romanceTropeFive;
        }
        else if (selectedGenre == "Science Fiction") {
            selectedMovies = scifiTropeFive;
        }
        numMovies = 5;
        break;
    default:
        cout << endl << "    Invalid choice. Redirecting you to the previous page." << endl;
        system("CLS");
        chooseTropes(selectedGenre);
    }

    // Sort the array of movies alphabetically by title
    mergeSort(selectedMovies, 0, numMovies - 1);

    // Display movie titles
    cout << "    ==============================================================" << endl;
    cout << "    ||                   MOVIE TITLES                           ||" << endl;
    cout << "    ==============================================================" << endl;
    for (int i = 0; i < numMovies; ++i) {
        cout << endl << "        " << i + 1 << ". " << selectedMovies[i].title << endl;
    }
    cout << endl << "    ==============================================================" << endl;

    int movieChoice;
    cout << endl << "        Enter the number of the movie you are interested in: ";
    cin >> movieChoice;

    system("CLS");

    if (movieChoice < 1 || movieChoice > numMovies) {
        system("CLS");

        int userChoice;
        cout << endl << endl << "    Invalid movie choice." << endl;
        cout << "    Press [1] to choose a movie again and [2] to exit. ";
        cin >> userChoice;
        if (userChoice == 1) {
            system("CLS");
            displayMoviesBasedOnTrope(selectedGenre, tropeChoice);
        }
        else if (userChoice == 2) {
            goodbyeExit();
        }
        else {
            do {
                cout << "    Press [1] to choose a movie again and [2] to exit. ";
                cin >> secondUserChoice;
                if (secondUserChoice == 1) {
                    system("CLS");
                    displayMoviesBasedOnTrope(selectedGenre, tropeChoice);
                }
                else if (secondUserChoice == 2) {
                    goodbyeExit();
                }
            } while (secondUserChoice != 1 && secondUserChoice != 2);
        }
        return;
    }

    // Display details of the selected movie
    cout << endl << endl;
    cout << "        ===============================================================" << endl;
    cout << "        ||                      MOVIE DETAILS                        ||" << endl;
    cout << "        ===============================================================" << endl;
    cout << "        Title:    " << selectedMovies[movieChoice - 1].title << endl;
    cout << "        Genre:    " << selectedMovies[movieChoice - 1].genre << endl;
    cout << "        Trope:    " << selectedMovies[movieChoice - 1].trope << endl;
    cout << "        Stars:    " << selectedMovies[movieChoice - 1].stars << endl;
    cout << "        ===============================================================" << endl;
    cout << "        +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "        ---------------------------------------------------------------" << endl;
    cout << "        |                                                             |" << endl;
    cout << "        |   [1] ADD TO MY LIST     [2]BACK TO HOMEPAGE    [3] EXIT    |  " << endl;
    cout << "        |                                                             |" << endl;
    cout << "        --------------------------------------------------------------" << endl;
    cout << "        ===============================================================" << endl << endl;

    int userChoice;
    cout << "                               YOUR CHOICE: ";
    cin >> userChoice;

    if (userChoice == 1) {
        system("CLS");
        string movieTitle = selectedMovies[movieChoice - 1].title;
        userMovieQueue.push(movieTitle);
        cout << endl << endl;
        cout << "        |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "        ===============================================================" << endl;
        cout << "        ||                                                           ||" << endl;
        cout << "        ||                  Movie  added to your list.               ||" << endl;
        cout << "        ||                                                           ||" << endl;
        cout << "        |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "        ===============================================================" << endl;
        cout << "                         [1] GO TO MY LIST        [2] EXIT                 " << endl;

        int userChoiceAgain;
        cout << "        ===============================================================" << endl;
        cout << "                                    YOUR CHOICE:";
        cin >> userChoiceAgain;

        if (userChoiceAgain == 1) {
            system("CLS");
            userList();
        }
        else if (userChoiceAgain == 2) {
            goodbyeExit();
        }
        else {
            int secondUserChoiceAgain;
            do {
                cout << "    Invalid choice. Press [1] to go to the Homepage and [2] to Exit: ";
                cout << "    ---------------------------------------------------------------- ";
                cin >> secondUserChoiceAgain;
                if (secondUserChoiceAgain == 1) {
                    system("CLS");
                    home();
                }
                else if (secondUserChoiceAgain == 2) {
                    goodbyeExit();
                }
            } while (secondUserChoiceAgain != 1 && secondUserChoiceAgain != 2);
        }
    }
    else if (userChoice == 2) {
        system("CLS");
        home();
    }
    else if (userChoice == 2) {
        system("CLS");
        goodbyeExit();
    }
    else {
        int secondUserChoice;
        do {
            cout << "    Invalid choice. Press [1] to go to the Homepage and [2] to Exit: ";
            cout << "    ---------------------------------------------------------------- ";
            cin >> secondUserChoice;
            if (secondUserChoice == 1) {
                system("CLS");
                home();
            }
            else if (secondUserChoice == 2) {
                goodbyeExit();
            }
        } while (secondUserChoice != 1 && secondUserChoice != 2);
    }
}

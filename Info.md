**Room**

    - Name (String)
    - LL of rooms that is connected to
        - LL Contains roomNodes containing rooms
        Functions Needed:
            add()
            pop()
            cleanup()
            print functions
    - LL of evidence left in room
    - Collection of hunters in room (unspecifed data structure)
    - Pointer to ghost in room
        - If ghost not in room, NULL
    - Need a function that takes in two rooms and connects two rooms together
    

**Bulding**

    Holds all info about hunt
    - Ghost (static or dynamic)
    - Collection of all hunters
    - LL of rooms
        - First room in LL is always hunter's van
    - Building is based on **"Willow Street House"** from Phasma. Link to map available in specs
    - Sample populate function provided in building.c, process from moving from van to hallways


**Ghost** 

    Moves between rooms and leaves evidence behind
    - GhostClass (Enum data type representing kind of ghost it is)
    - Pointer to room it is in
    - Boredom timer (set to BOREDOM_MAX)
        - Each time in room with hunter, timer is reset to MAX
        - Each time in room without hunter, timer decreases by 1, if timer reaches <= 0, gets bored and ends haunting
    Ghosts take one of two actions:
    1. Random chance to generate evidence to add to room, or it will move or it will do nothing
    2. If in room with hunter, it will not choose to move, but it may choose to take no action
    Actions chosn at random.

    There is only ever ONE ghost in a building.
    Each ghost leaves 3 of the 4 EvidenceTypes at random, defined in table: 
    Table1.
    A Ghost can be: 
    POLTER
    BANSHEE
    BULLIES,
    PHANTOM

**Hunter**

    Move rooms
    Read room for evi
    Communicataes evi

    - Pointer to current room
    - Enum for evi type that they can read
    - Collection of collected evi by them
    - Name
    - Fear int start at 0
    Choose action at random
    If in room with ghost, when they make decision +1 fear
    If 100 fear, close thread.
    Can add logic to decisions
    Document behav's in README
    If in same room as another hunter, they can communicate.
        - If they communicate append ghostly evidence data to the other hunter's collection. 
    - Integer time variable representing interest. If time <= 0, leave building
        If they see ghostly evidence, reset timer

**Evidence**

    Contains evidence class
    Value for data of reading.
    Stored as:
        - EMF 
        - TEMPERATURE
        - FINGERPRINTS
        - SOUNDS
    - Have either Standard Reading or Ghost Reading. NOT FIELDS
    - Generated based on the value of the interval.
    If ghost generates evidence that is within standard readings, it cannot be used to confirm its type.
    Stored by each hunter and in each room. Once evidence is found, it is no longer in room. Multiple hunters can point to the same evidence. 

    Ghosts and their Evidence Types:
        POLTERGEIST: Leaves ghostly EMF, TEMPERATURE, and FINGERPRINTS
        BANSHEE: Leaves ghostly EMF, TEMPERATURE, and SOUND
        BULLIES: Leaves ghostly EMF, FINGERPRINTS, and SOUND
        PHANTOM: Leaves ghostly TEMPERATURE, FINGERPRINTS, and SOUND





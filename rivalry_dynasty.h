#ifndef RIVALRY_DYNASTY_H
#define RIVALRY_DYNASTY_H

#include <string>
#include <vector>

// ============================================================
//  rivalry_dynasty.h
//  Feature: Rivalry Dynasty Mode — EA Sports College Football
//  Description: Class definitions for the Rivalry Dynasty Mode
//               subsystem. Implements the Strategy Design Pattern
//               via abstract Personality, NeedsManager, CareerTrack,
//               and RivalryEvent components composed into Sim.
// ============================================================


// ============================================================
//  LAYER 2 — ABSTRACT STRATEGY COMPONENTS
// ============================================================

// Forward declaration
class Sim;

/**
 * Abstract base class for personality traits.
 * Concrete subclasses define specific trait behaviours
 * that influence Sim performance in high-pressure situations.
 */
class Personality {
protected:
    std::string traitName;
    float intensity;

public:
    virtual ~Personality() {}

    // Apply this trait's effect to the given Sim
    virtual void applyEffect(Sim& sim) = 0;

    // Evolve the trait based on career performance
    virtual void evolve() = 0;

    std::string getTraitName() const;
    float getIntensity() const;
};


/**
 * Abstract base class for managing a Sim's core needs.
 * Concrete subclasses implement decay rates appropriate
 * to the Sim's role (e.g. athlete vs. standard Sim).
 */
class NeedsManager {
protected:
    float energy;
    float social;
    float academic;

public:
    virtual ~NeedsManager() {}

    // Decay all needs over the given time delta
    virtual void decay(float deltaTime) = 0;

    // Returns true if any need has reached a critical level
    virtual bool isCritical() const = 0;

    float getEnergy() const;
    float getSocial() const;
    float getAcademic() const;
};


/**
 * Abstract base class for career progression tracking.
 * Subclasses define career arcs for different roles
 * (e.g. coach, player) with milestone logic.
 */
class CareerTrack {
protected:
    int legacyPoints;
    std::vector<std::string> milestones;

public:
    virtual ~CareerTrack() {}

    // Award a number of legacy points
    virtual void awardPoints(int n) = 0;

    // Check whether any milestone has been reached
    virtual void checkMilestone() = 0;

    int getLegacyPoints() const;
    const std::vector<std::string>& getMilestones() const;
};


/**
 * Abstract base class for rivalry match events.
 * Subclasses implement specific rivalry types and
 * define how the rivalry meter behaves during a game.
 */
class RivalryEvent {
protected:
    float rivalryMeter;
    std::vector<std::string> challengeList;

public:
    virtual ~RivalryEvent() {}

    // Trigger the rivalry event
    virtual void trigger() = 0;

    // Update the rivalry meter by a given delta
    virtual void updateMeter(float delta) = 0;

    float getRivalryMeter() const;
};


// ============================================================
//  LAYER 3 — CONCRETE PERSONALITY IMPLEMENTATIONS
// ============================================================

/**
 * A Sim with the Leader trait provides a morale boost
 * to nearby teammates during high-pressure moments.
 */
class Leader : public Personality {
private:
    float boostRadius;

public:
    Leader(float radius = 10.0f);

    void applyEffect(Sim& sim) override;
    void evolve() override;
};


/**
 * A Sim with the HotHeaded trait is prone to penalties
 * when rivalry crowd noise exceeds a threshold.
 */
class HotHeaded : public Personality {
private:
    float penaltyChance;

public:
    HotHeaded(float chance = 0.25f);

    void applyEffect(Sim& sim) override;
    void evolve() override;
};


/**
 * A Sim with the ClutchPerformer trait receives a
 * ratings boost when the game is on the line.
 */
class ClutchPerformer : public Personality {
private:
    float pressureThreshold;

public:
    ClutchPerformer(float threshold = 0.75f);

    void applyEffect(Sim& sim) override;
    void evolve() override;
};


// ============================================================
//  LAYER 3 — CONCRETE NEEDS IMPLEMENTATION
// ============================================================

/**
 * NeedsManager implementation for athlete Sims.
 * Energy decays faster due to training load;
 * academic needs require careful scheduling.
 */
class AthleteNeeds : public NeedsManager {
private:
    float trainingLoad;

public:
    AthleteNeeds(float load = 1.0f);

    void decay(float deltaTime) override;
    bool isCritical() const override;
};


// ============================================================
//  LAYER 3 — CONCRETE CAREER IMPLEMENTATION
// ============================================================

/**
 * CareerTrack implementation for coaching staff.
 * Tracks rivalry wins, awards, and Hall of Fame eligibility.
 */
class CoachCareer : public CareerTrack {
private:
    bool hallOfFame;

public:
    CoachCareer();

    void awardPoints(int n) override;
    void checkMilestone() override;

    bool isHallOfFame() const;
};


// ============================================================
//  LAYER 3 — CONCRETE RIVALRY EVENT IMPLEMENTATION
// ============================================================

/**
 * A scheduled weekly rivalry matchup between two teams.
 * Triggers special UI, amplifies the rivalry meter, and
 * awards a legacy trophy on completion.
 */
class WeeklyRivalryEvent : public RivalryEvent {
private:
    std::string homeTeam;
    std::string awayTeam;

public:
    WeeklyRivalryEvent(const std::string& home, const std::string& away);

    void trigger() override;
    void updateMeter(float delta) override;
    int awardTrophy(); // Returns legacy points to be routed by DynastyManager
    
    std::string getHomeTeam() const;
    std::string getAwayTeam() const;
};


// ============================================================
//  LAYER 1 — ROOT COMPOSITE
// ============================================================

/**
 * The central Sim class. Behaviour is delegated to
 * strategy components (Personality, NeedsManager,
 * CareerTrack) following the composition-over-inheritance
 * principle.
 */
class Sim {
private:
    //Personality*   personality;
    //NeedsManager*  needs;
    //CareerTrack*   career;
    std::unique_ptr<Personality>  personality;
    std::unique_ptr<NeedsManager> needs;
    std::unique_ptr<CareerTrack>  career;
    int            rivalryScore;

public:
    // Takes ownership of p, n, and c via unique_ptr on construction
    Sim(std::unique_ptr<Personality> p, std::unique_ptr<NeedsManager> n, std::unique_ptr<CareerTrack> c);
    ~Sim()= default; // unique_ptr handles cleanup automatically;

    // Update the Sim each game tick
    void update();

    // Participate in a rivalry event
    void participateInRivalry(RivalryEvent& event);

    // Return accumulated legacy points from career track
    int getLegacyPoints() const;

    // Accessors
    int getRivalryScore() const;
    void addRivalryScore(int points);
    Personality* getPersonality() const;
    NeedsManager* getNeeds() const;
    CareerTrack* getCareer() const;
};


// ============================================================
//  LAYER 4 — MANAGER / CONTROLLER
// ============================================================

/**
 * Orchestrates the dynasty simulation across seasons.
 * Manages the roster of Sims, schedules rivalry events,
 * and checks for legacy milestones.
 */
class DynastyManager {
private:
    int                          season;
    std::vector<std::unique_ptr<Sim>>          roster;  // DynastyManager owns these
    std::vector<std::unique_ptr<RivalryEvent>> events;  // DynastyManager owns these

public:
    DynastyManager();
    ~DynastyManager();

    // Advance to the next season
    void advanceSeason();

    // Schedule a new rivalry event
    void scheduleRivalry(RivalryEvent* event);

    // Compute and display current standings
    void computeStandings();

    // Check all Sims for legacy milestones
    void checkLegacy();

    // Roster management
    void addSim(Sim* sim);
    void removeSim(Sim* sim);

    int getSeason() const;
};


#endif // RIVALRY_DYNASTY_H

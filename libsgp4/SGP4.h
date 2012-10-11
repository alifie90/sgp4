#ifndef SGP4_H_
#define SGP4_H_

#include "Tle.h"
#include "OrbitalElements.h"
#include "Eci.h"
#include "SatelliteException.h"
#include "DecayedException.h"

class SGP4
{
public:
    SGP4(const Tle& tle)
        : elements_(tle)
    {
        Initialise();
    }

    virtual ~SGP4()
    {
    }

    void SetTle(const Tle& tle);
    Eci FindPosition(double tsince) const;
    Eci FindPosition(const DateTime& date) const;

    struct CommonConstants
    {
        double cosio;
        double sinio;
        double eta;
        double t2cof;
        double a3ovk2;
        double x1mth2;
        double x3thm1;
        double x7thm1;
        double aycof;
        double xlcof;
        double xnodcf;
        double c1;
        double c4;
        double omgdot; // secular rate of omega (radians/sec)
        double xnodot; // secular rate of xnode (radians/sec)
        double xmdot;  // secular rate of xmo   (radians/sec)
    };

    struct NearSpaceConstants
    {
        double c5;
        double omgcof;
        double xmcof;
        double delmo;
        double sinmo;
        double d2;
        double d3;
        double d4;
        double t3cof;
        double t4cof;
        double t5cof;
    };

    struct DeepSpaceConstants
    {
        double gsto;
        double zmol;
        double zmos;
        /*
         * whether the deep space orbit is
         * geopotential resonance for 12 hour orbits
         */
        bool resonance_flag;
        /*
         * whether the deep space orbit is
         * 24h synchronous resonance
         */
        bool synchronous_flag;
        /*
         * lunar / solar constants for epoch
         * applied during DeepSpaceSecular()
         */
        double sse;
        double ssi;
        double ssl;
        double ssg;
        double ssh;
        /*
         * lunar / solar constants
         * used during DeepSpaceCalculateLunarSolarTerms()
         */
        double se2;
        double si2;
        double sl2;
        double sgh2;
        double sh2;
        double se3;
        double si3;
        double sl3;
        double sgh3;
        double sh3;
        double sl4;
        double sgh4;
        double ee2;
        double e3;
        double xi2;
        double xi3;
        double xl2;
        double xl3;
        double xl4;
        double xgh2;
        double xgh3;
        double xgh4;
        double xh2;
        double xh3;
        /*
         * used during DeepSpaceCalcDotTerms()
         */
        double d2201;
        double d2211;
        double d3210;
        double d3222;
        double d4410;
        double d4422;
        double d5220;
        double d5232;
        double d5421;
        double d5433;
        double del1;
        double del2;
        double del3;
    };

    struct IntegratorValues
    {
        double xndot;
        double xnddt;
        double xldot;
    };

    struct IntegratorConstants
    {
        /*
         * integrator constants
         */
        double xfact;
        double xlamo;

        /*
         * integrator values for epoch
         */
        struct IntegratorValues values_0;
    };

    struct IntegratorParams
    {
        /*
         * integrator values
         */
        double xli;
        double xni;
        double atime;
        /*
         * itegrator values for current d_atime_
         */
        struct IntegratorValues values_t;
    };

private:
    void Initialise();
    Eci FindPositionSDP4(const double tsince) const;
    Eci FindPositionSGP4(double tsince) const;
    Eci CalculateFinalPositionVelocity(
            const double tsince,
            const double e,
            const double a,
            const double omega,
            const double xl,
            const double xnode,
            const double xincl,
            const double xlcof,
            const double aycof,
            const double x3thm1,
            const double x1mth2,
            const double x7thm1,
            const double cosio,
            const double sinio) const;
    void DeepSpaceInitialise(
            const double eosq,
            const double sinio,
            const double cosio,
            const double betao,
            const double theta2,
            const double betao2,
            const double xmdot,
            const double omgdot,
            const double xnodot);
    void DeepSpaceCalculateLunarSolarTerms(
            const double tsince,
            double& pe,
            double& pinc,
            double& pl,
            double& pgh,
            double& ph) const;
    void DeepSpacePeriodics(
            const double tsince,
            double& em,
            double& xinc,
            double& omgasm,
            double& xnodes,
            double& xll) const;
    void DeepSpaceSecular(
            const double tsince,
            double& xll,
            double& omgasm,
            double& xnodes,
            double& em,
            double& xinc,
            double& xn) const;
    void DeepSpaceCalcDotTerms(struct IntegratorValues& values) const;
    void DeepSpaceIntegrator(
            const double delt,
            const double step2,
            const struct IntegratorValues& values) const;
    void Reset();

    /*
     * flags
     */
    bool use_simple_model_;
    bool use_deep_space_;

    /*
     * the constants used
     */
    struct CommonConstants common_consts_;
    struct NearSpaceConstants nearspace_consts_;
    struct DeepSpaceConstants deepspace_consts_;
    struct IntegratorConstants integrator_consts_;
    mutable struct IntegratorParams integrator_params_;

    /*
     * the orbit data
     */
    OrbitalElements elements_;
};

#endif

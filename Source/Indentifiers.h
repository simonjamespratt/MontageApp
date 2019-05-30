/*
  ==============================================================================

    Indentifiers.h
    Created: 20 Apr 2019 12:07:58pm
    Author:  Simon Pratt

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

static Identifier appStateIdentifier("AppState");

// Sources
static Identifier sourcesIdentifier("Sources");
static Identifier sourceIdentifier("Source");
static Identifier sourcePropIdIdentifier("id");
static Identifier sourcePropFilePathIdentifier("filePath");
static Identifier sourcePropFileNameIdentifier("fileName");

// Particles
static Identifier particlesIdentifier("Particles");
static Identifier particleIdentifier("Particle");
static Identifier particlePropIdIdentifier("id");
static Identifier particlePropNameIdentifier("name");
static Identifier particlePropSourceIdIdentifier("sourceId");
static Identifier particlePropRangeStartIdentifier("rangeStart");
static Identifier particlePropRangeEndIdentifier("rangeEnd");

// Figures
static Identifier figuresIdentifier("Figures");
static Identifier figureIdentifier("Figure");
static Identifier figurePropIdIdentifier("figureId");
static Identifier figureEventIdentifier("FigureEvent");
static Identifier figureEventPropIdIdentifier("figureEventId");
static Identifier figureEventPropOnsetIdentifier("onset");
static Identifier figureEventPropParticleIdIdentifier("particleId");

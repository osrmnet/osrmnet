// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once
#include "OsrmFwdDecl.h"

namespace osrmnet
{
	enum class GeometriesType;
	ref class RouteLeg;
	ref class RouteParameters;
	ref class Coordinate;
	
	public ref class RouteResult
	{		
	public:
		property double Distance;
		property double Duration;
		property GeometriesType Geometry;
		property System::Collections::Generic::IList<RouteLeg^>^ Legs;

		RouteResult()
		{
			Legs = gcnew System::Collections::Generic::List<RouteLeg^>();
		}

		static System::Collections::Generic::IEnumerable<osrmnet::RouteResult^>^ FromJsonObject(osrm::util::json::Object&, osrmnet::RouteParameters^);

	};

	public ref class Annotation
	{
	public:
		property System::Collections::Generic::IList<double>^ Distance;
		property System::Collections::Generic::IList<double>^ Duration;
		property System::Collections::Generic::IList<long long>^ Nodes;

		Annotation()
		{
			Distance = gcnew System::Collections::Generic::List<double>();
			Duration = gcnew System::Collections::Generic::List<double>();
			Nodes = gcnew System::Collections::Generic::List<long long>();
		}
	};

	public ref class Lane
	{
	public:
		property System::Collections::Generic::IList<System::String^>^ Indications;
		property System::Boolean Valid;

		Lane()
		{
			Indications = gcnew System::Collections::Generic::List<System::String^>();
		}
	};

	public ref class Intersection
	{
	public:
		property System::Nullable<int> Out;
		property System::Nullable<int> In;
		property System::Collections::Generic::IList<System::Boolean>^ Entry;
		property System::Collections::Generic::IList<int>^ Bearings;
		property Coordinate^ Location;
		property System::Collections::Generic::IList<System::String^>^ Lanes;

		Intersection()
		{
			Entry = gcnew System::Collections::Generic::List<System::Boolean>();
			Bearings = gcnew System::Collections::Generic::List<int>();
			Lanes = gcnew System::Collections::Generic::List<System::String^>();
		}
	};

	public ref class Maneuver
	{
	public:
		property int BearingAfter;
		property osrmnet::Coordinate^ Location;
		property int BearingBefore;
		property System::String^ Type;
		property System::String^ Modifier;
		property System::Nullable<int> Exit;

		Maneuver()
		{
		}
	};

	public ref class RouteStep
	{
	public:
		property double Distance;
		property double Duration;
		property System::String^ Name;
		property System::String^ Geometry;
		property System::String^ Mode;
		property System::Collections::Generic::IList<osrmnet::Intersection^>^ Intersections;
		property osrmnet::Maneuver^ Maneuver;
		
		//Optionals
		property System::Nullable<double> Weight;
		property System::Nullable<int> Ref;
		property System::String^ Pronounciation;
		property System::String^ Destinations;
		property System::String^ RotaryName;
		property System::String^ RotaryPronounciation;




		RouteStep()
		{
			Intersections = gcnew System::Collections::Generic::List<osrmnet::Intersection^>();
			Maneuver = gcnew osrmnet::Maneuver();
		}

	};

	public ref class RouteLeg
	{
	public:
		property double Distance;
		property double Duration;
		property System::String^ Summary;
		property System::Collections::Generic::IList<osrmnet::RouteStep^>^ Steps;
		property osrmnet::Annotation^ Annotation;

		RouteLeg()
		{
			Steps = gcnew System::Collections::Generic::List<osrmnet::RouteStep^>();
		}
	};
}

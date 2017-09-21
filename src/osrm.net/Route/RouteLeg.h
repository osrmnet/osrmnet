// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once
#include "..\OsrmFwdDecl.h"

using namespace System::Collections::Generic;

namespace Osrmnet {
	ref class Coordinate;
	ref class Geometry;

	namespace Route {
		public ref class Annotation
		{
		public:
			property IList<double>^ Speed;
			property IList<double>^ Duration;
			property IList<long long>^ Nodes;
			property IList<double>^ Distance;
			property IList<int>^ Datasources;
			property IList<double>^ Weight;

			Annotation()
			{
				Speed = gcnew List<double>();
				Duration = gcnew List<double>();
				Nodes = gcnew List<long long>();
				Distance = gcnew List<double>();
				Datasources = gcnew List<int>();
				Weight = gcnew List<double>();
			}
		};

		public ref class Lane
		{
		public:
			property IList<System::String^>^ Indications;
			property System::Boolean Valid;

			Lane()
			{
				Indications = gcnew List<System::String^>();
			}
		};

		public ref class Intersection
		{
		public:
			property System::Nullable<int> Out;
			property System::Nullable<int> In;
			property IList<System::Boolean>^ Entry;
			property IList<int>^ Bearings;
			property Coordinate^ Location;
			property IList<Lane^>^ Lanes;

			Intersection()
			{
				Entry = gcnew List<System::Boolean>();
				Bearings = gcnew List<int>();
				Lanes = gcnew List<Lane^>();
			}
		};

		public ref class Maneuver
		{
		public:
			property int BearingAfter;
			property Coordinate^ Location;
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
			property Geometry^ Geometry;
			property System::String^ Mode;
			property IList<Intersection^>^ Intersections;
			property Maneuver^ Maneuver;

			//Optionals
			property System::Nullable<double> Weight;
			property System::Nullable<int> Ref;
			property System::String^ Pronounciation;
			property System::String^ Destinations;
			property System::String^ RotaryName;
			property System::String^ RotaryPronounciation;

			RouteStep()
			{
				Intersections = gcnew List<Intersection^>();
			}
		};

		public ref class RouteLeg
		{
		public:
			property double Distance;
			property double Duration;
			property System::String^ Summary;
			property IList<RouteStep^>^ Steps;
			property Annotation^ Annotation;

			RouteLeg()
			{
				Steps = gcnew List<RouteStep^>();
			}
		};
	}
}

// Copyright (c) 2016 Surya Suluh and contributors.  All rights reserved.
// Licensed under the MIT License.  See included LICENSE in the project root for license information.

#pragma once
#include "OsrmFwdDecl.h"

namespace osrmnet
{
	enum class GeometriesType;
	ref class RouteLeg;
	ref struct Coordinate;
	ref class RouteParameters;

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
		property System::Collections::Generic::IList<unsigned long long>^ Nodes;

		Annotation()
		{
			Distance = gcnew System::Collections::Generic::List<double>();
			Duration = gcnew System::Collections::Generic::List<double>();
			Nodes = gcnew System::Collections::Generic::List<unsigned long long>();
		}
	};

	public ref class Geometry
	{
	public:
		Geometry()
		{
			Coordinates = gcnew System::Collections::Generic::List<Coordinate^>();
		}

		property System::Collections::Generic::IList<osrmnet::Coordinate^>^ Coordinates;
	};

	public ref class RouteStep
	{
		property double Distance;
		property double Duration;
		property System::String^ Name;
		property System::String^ Pronounciation;
		property Geometry^ Geometry;
		property System::String^ Mode;
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

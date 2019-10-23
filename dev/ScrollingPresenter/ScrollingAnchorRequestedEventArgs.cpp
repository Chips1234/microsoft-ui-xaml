﻿// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "common.h"
#include "Vector.h"
#include "ScrollingPresenter.h"
#include "ScrollingPresenterTrace.h"
#include "ScrollingAnchorRequestedEventArgs.h"

ScrollingAnchorRequestedEventArgs::ScrollingAnchorRequestedEventArgs(const winrt::ScrollingPresenter& scrollingPresenter)
{
    SCROLLINGPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR, METH_NAME, this, scrollingPresenter);

    m_scrollingPresenter.set(scrollingPresenter);
}

#pragma region IScrollingAnchorRequestedEventArgs

winrt::IVector<winrt::UIElement> ScrollingAnchorRequestedEventArgs::AnchorCandidates()
{
    return m_anchorCandidates.get();
}

winrt::UIElement ScrollingAnchorRequestedEventArgs::AnchorElement()
{
    return m_anchorElement.get();
}

void ScrollingAnchorRequestedEventArgs::AnchorElement(winrt::UIElement const& value)
{
    SCROLLINGPRESENTER_TRACE_VERBOSE(nullptr, TRACE_MSG_METH_PTR, METH_NAME, this, value);

    const winrt::UIElement& anchorElement{ value };
    com_ptr<ScrollingPresenter> scrollingPresenter = winrt::get_self<ScrollingPresenter>(m_scrollingPresenter.get())->get_strong();

    if (!anchorElement || scrollingPresenter->IsElementValidAnchor(anchorElement))
    {
        m_anchorElement.set(anchorElement);
    }
    else
    {
        throw winrt::hresult_error(E_INVALIDARG);
    }
}

#pragma endregion

winrt::IVector<winrt::UIElement> ScrollingAnchorRequestedEventArgs::GetAnchorCandidates()
{
    return m_anchorCandidates.get();
}

void ScrollingAnchorRequestedEventArgs::SetAnchorCandidates(const std::vector<tracker_ref<winrt::UIElement>>& anchorCandidates)
{
    winrt::IVector<winrt::UIElement> anchorCandidatesTmp = winrt::make<Vector<winrt::UIElement, MakeVectorParam<VectorFlag::DependencyObjectBase>()>>();
        
    for (tracker_ref<winrt::UIElement> anchorCandidate : anchorCandidates)
    {
        anchorCandidatesTmp.Append(anchorCandidate.get());
    }
    m_anchorCandidates.set(anchorCandidatesTmp);
}

winrt::UIElement ScrollingAnchorRequestedEventArgs::GetAnchorElement() const
{
    return m_anchorElement.get();
}

void ScrollingAnchorRequestedEventArgs::SetAnchorElement(const winrt::UIElement& anchorElement)
{
    m_anchorElement.set(anchorElement);
}

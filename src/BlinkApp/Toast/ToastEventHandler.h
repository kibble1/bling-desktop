#pragma once

#include <functional>

typedef ABI::Windows::Foundation::ITypedEventHandler<ABI::Windows::UI::Notifications::ToastNotification *, ::IInspectable *> DesktopToastActivatedEventHandler;
typedef ABI::Windows::Foundation::ITypedEventHandler<ABI::Windows::UI::Notifications::ToastNotification *, ABI::Windows::UI::Notifications::ToastDismissedEventArgs *> DesktopToastDismissedEventHandler;
typedef ABI::Windows::Foundation::ITypedEventHandler<ABI::Windows::UI::Notifications::ToastNotification *, ABI::Windows::UI::Notifications::ToastFailedEventArgs *> DesktopToastFailedEventHandler;

class ToastEventHandler :
    public Microsoft::WRL::Implements<DesktopToastActivatedEventHandler, DesktopToastDismissedEventHandler, DesktopToastFailedEventHandler>
{
public:
	ToastEventHandler::ToastEventHandler(std::function<bool()> activated, std::function<bool()> dismissed, std::function<bool()> failed);
    ~ToastEventHandler();
        
    // DesktopToastActivatedEventHandler 
    IFACEMETHODIMP Invoke(_In_ ABI::Windows::UI::Notifications::IToastNotification *sender, _In_ IInspectable* args) override;

    // DesktopToastDismissedEventHandler
    IFACEMETHODIMP Invoke(_In_ ABI::Windows::UI::Notifications::IToastNotification *sender, _In_ ABI::Windows::UI::Notifications::IToastDismissedEventArgs *e) override;
        
    // DesktopToastFailedEventHandler
    IFACEMETHODIMP Invoke(_In_ ABI::Windows::UI::Notifications::IToastNotification *sender, _In_ ABI::Windows::UI::Notifications::IToastFailedEventArgs *e) override;

    // IUnknown
    IFACEMETHODIMP_(ULONG) AddRef() { return InterlockedIncrement(&_ref); }

    IFACEMETHODIMP_(ULONG) Release() {
        ULONG l = InterlockedDecrement(&_ref);
        if (l == 0) delete this;
        return l;
    }

    IFACEMETHODIMP QueryInterface(_In_ REFIID riid, _COM_Outptr_ void **ppv) {
        if (IsEqualIID(riid, IID_IUnknown))
            *ppv = static_cast<IUnknown*>(static_cast<DesktopToastActivatedEventHandler*>(this));
        else if (IsEqualIID(riid, __uuidof(DesktopToastActivatedEventHandler)))
            *ppv = static_cast<DesktopToastActivatedEventHandler*>(this);
        else if (IsEqualIID(riid, __uuidof(DesktopToastDismissedEventHandler)))
            *ppv = static_cast<DesktopToastDismissedEventHandler*>(this);
        else if (IsEqualIID(riid, __uuidof(DesktopToastFailedEventHandler)))
            *ppv = static_cast<DesktopToastFailedEventHandler*>(this);
        else *ppv = nullptr;

        if (*ppv) {
            reinterpret_cast<IUnknown*>(*ppv)->AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }
    
private:
    ULONG _ref;
    
	std::function<bool()> m_activated;
	std::function<bool()> m_dismissed;
	std::function<bool()> m_failed;
};
